/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:27:51 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/18 10:33:05 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "lem_in.h"

int		read_ants(int *ants)
{
	char	*line;
	int		st;

	st = ER_DATA_EMPTY;
	line = NULL;
	if (get_next_line(0, &line))
	{
		if (ft_isvldint(line) && line[0] != '-')
		{
			*ants = ft_atoi(line);
			if (*ants)
				st = 1;
		}
		else
			st = ER_ANTS_INV_NUMBER;
		ft_strdel(&line);
	}
	return (st);
}

void	print_links(t_list *node)
{
	t_node *room;

	room = (t_node*)node->content;
	ft_printf("name -> %s\n", room->name);
	ft_printf("d -> %d\n", room->d);
	ft_printf("p -> %d\n", room->p);
}

void	print(t_list *node)
{
	ft_printf("%d\n", *(int*)node->content);
}

void	choose_one(t_list **paths, t_list *path, int idx)
{
	t_list *second;

	second = ft_lstget(*paths, idx);
	if (ft_lstlen(path) < ft_lstlen(second))
	{
		second->content = path->content;
		second->content_size = path->content_size;
	}
}

/*
** Magic in case when start and end is the only nodes.
*/

t_list	*get_paths(t_lmdata *data)
{
	t_list	*path;
	t_list	*paths;
	t_list	*black_list;
	int		magic;

	path = NULL;
	paths = NULL;
	black_list = NULL;
	bfs(data, black_list);
	magic = 0;
	if (((t_node*)((t_list*)data->extra->scd)->content)->p == \
			get_node_idx(data, ((t_node*)((t_list*)data->extra->fst)->content)->name))
		magic = 1;
	while (((t_node*)((t_list*)data->extra->scd)->content)->p != -1)
	{
		save_path(data, &path);
		ft_lstadd(&paths, ft_lstnew(path, sizeof(t_list)));
		add_path_to_blacklist(&black_list, path);
		wash_up_map(data);
		if (!magic)
			bfs(data, black_list);
		path = NULL;
	}
	return (paths);
}

void	init_data(t_lmdata **data, char **line, t_rdata *rdata)
{
	*line = NULL;
	rdata->cmd_mode = 0;
	rdata->data_type = 0;
	*data = new_data(1);
}

void	parse(t_lmdata **data, char **line, t_rdata *rdata)
{
	if (rdata->data_type == 0 && (*line)[0] == '#' && (*line)[1] == '#')
		rdata->pr = parse_command(*line, &rdata->cmd_mode, (*data)->extra);
	else if ((*line)[0] == '#')
		rdata->pr = 1;
	else if (rdata->data_type == 0 \
			&& (rdata->pr = parse_room(*line, *data, rdata->cmd_mode, (*data)->extra)))
		rdata->cmd_mode = 0;
	else if ((*data)->extra->fst && (*data)->extra->scd)
	{
		rdata->data_type = 1;
		rdata->pr = parse_link(*line, *data);
	}
	else
		rdata->pr = ER_PASS_FURTHER;
}

t_lmdata *read_data(void)
{
	t_lmdata	*data;
	char 		*line;
	t_rdata		rdata;

	data = NULL;
	init_data(&data, &line, &rdata);
	rdata.pr = read_ants(&data->ants);
	while (rdata.pr == 1 && get_next_line(0, &line))
	{
		parse(&data, &line, &rdata);
		ft_strdel(&line);
	}
	if (rdata.pr == 1 && (!data->extra->fst || !data->extra->scd))
		rdata.pr = ER_PASS_FURTHER;
	if (rdata.pr == ER_PASS_FURTHER && !data->extra->fst && !data->extra->scd)
		rdata.pr = ER_DATA_NO_START_END;
	else if  (rdata.pr == ER_PASS_FURTHER && !data->extra->fst)
		rdata.pr = ER_DATA_NO_START;
	else if (rdata.pr == ER_PASS_FURTHER && !data->extra->scd)
		rdata.pr = ER_DATA_NO_END;
	if (rdata.pr != 1)
	{
		error_handler(rdata.pr);
		return (NULL);
	}
	return (data);
}

int		main(void)
{
	t_list		*paths;
	t_lmdata	*data;

	data = read_data();
	if (data)
	{
		if ((paths = get_paths(data)))
			pdecode_paths(data, paths);
		else
			ft_printf("Error: no path between start and end\n");
	}
	return (0);
}
