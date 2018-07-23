/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:27:51 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/23 12:06:13 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "lem_in.h"

t_err	*read_ants(int *ants)
{
	char		*line;
	t_err_code	st;
	t_err		*err;

	st = ERR_DATA_EMPTY;
	err = NULL;
	line = NULL;
	if (get_next_line(0, &line))
	{
		if (ft_isvldint(line) && line[0] != '-')
		{
			*ants = ft_atoi(line);
			if (*ants)
				st = ERR_NONE;
		}
		else
			err = raise_ants_inv_number(line);
		ft_strdel(&line);
	}
	if (!err && st != ERR_NONE)
		err = raise_data_empty();
	return (err);
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

/*
** Magic in case when start and end is the only nodes.
*/

t_list	*get_paths(t_lmdata *data)
{
	t_list	*path;
	t_list	*paths;
	t_list	*black_list;

	path = NULL;
	paths = NULL;
	black_list = NULL;
	bfs(data, black_list);
	while (((t_node*)((t_list*)data->extra->scd)->content)->p != -1)
	{
		save_path(data, &path);
		ft_lstadd(&paths, ft_lstnew(path, sizeof(t_list)));
		add_path_to_blacklist(&black_list, path);
		// In case start-end + some other paths
		if (((t_node*)((t_list*)data->extra->scd)->content)->p == \
				get_node_idx(data, ((t_node*)((t_list*)data->extra->fst)->content)->name))
		{
			del_link(data, ((t_node*)((t_list*)data->extra->fst)->content)->name,
					((t_node*)((t_list*)data->extra->scd)->content)->name);
		}
		wash_up_map(data);
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
	char **arr;

	arr = ft_strsplit(*line, ' ');
	if (rdata->data_type == 0 && (*line)[0] == '#' && (*line)[1] == '#')
		rdata->err = parse_command(*line, &rdata->cmd_mode, (*data)->extra);
	else if ((*line)[0] == '#')
		return ;
	else if (rdata->data_type == 0 && !(arr[0] && ft_strchr(arr[0], '-')) && \
			!(rdata->err = parse_room(*line, *data, rdata->cmd_mode, (*data)->extra)))
		rdata->cmd_mode = 0;
	else if (!rdata->err && (*data)->extra->fst && (*data)->extra->scd)
	{
		rdata->data_type = 1;
		rdata->err = parse_link(*line, *data);
	}
	else if (!rdata->err)
		rdata->err = new_err(ERR_PASS_FURTHER, NULL, 0);
}

void	realloc_arr(char ***arr, int old_size, int new_size)
{
	int		i;
	char	**narr;

	i = -1;
	narr = (char **)ft_memalloc(new_size * sizeof(char*));
	if (arr && *arr)
	{
		while (++i < old_size)
			narr[i] = (*arr)[i];
		ft_memdel((void**)arr);
	}
	*arr = narr;
}

t_lmdata *read_data(void)
{
	t_lmdata	*data;
	char 		*line;
	t_rdata		rdata;
	int			lc;
	char		**input;
	int			arr_size;
	int			i;

	lc = 1;
	arr_size = 1;
	i = 0;
	data = NULL;
	input = NULL;
	realloc_arr(&input, 0, arr_size);
	init_data(&data, &line, &rdata);
	rdata.err = read_ants(&data->ants);
	input[i++] = ft_itoa(data->ants);
	while (!rdata.err && get_next_line(0, &line))
	{
		parse(&data, &line, &rdata);
		if (i >= arr_size)
		{
			realloc_arr(&input, arr_size, arr_size * 2);
			arr_size *= 2;
		}
		if (rdata.err && rdata.err->err_code == ERR_CMD_INV)
			rdata.err = NULL;
		// i can't ignore bad commands !
		input[i++] = line;
		++lc;
	}
	if (rdata.err)
		rdata.err->line = lc;
	if (rdata.err && rdata.err->err_code == ERR_ROOM_DOUBLE_DEF)
		li_room_double_def(rdata.err, input, i);
	if (rdata.err && (rdata.err->err_code == ERR_CMD_DOUBLE_START || rdata.err->err_code == ERR_CMD_DOUBLE_END))
		li_cmd_double(rdata.err, input, i);
	if (rdata.err && rdata.err->err_code == ERR_LINK_DOUBLE)
		li_link_double(rdata.err, input, i);
	if (!rdata.err && (!data->extra->fst || !data->extra->scd))
		rdata.err = new_err(ERR_PASS_FURTHER, NULL, 0);
	if (rdata.err && rdata.err->err_code == ERR_PASS_FURTHER && !data->extra->fst && !data->extra->scd)
		rdata.err = raise_data_no_start_end();
	else if  (rdata.err && rdata.err->err_code == ERR_PASS_FURTHER && !data->extra->fst)
		rdata.err = raise_data_no_start();
	else if (rdata.err && rdata.err->err_code == ERR_PASS_FURTHER && !data->extra->scd)
		rdata.err = raise_data_no_end();
	if (rdata.err)
	{
		error_handler(rdata.err);
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
