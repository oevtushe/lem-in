/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:27:51 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/26 11:40:41 by oevtushe         ###   ########.fr       */
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
	int		dl;

	dl  = 0;
	path = NULL;
	paths = NULL;
	black_list = NULL;
	bfs(data, black_list);
	while (((t_node*)((t_list*)data->extra->scd)->content)->p != -1)
	{
		save_path(data, &path);
		ft_lstappend(&paths, ft_lstnew(path, sizeof(t_list)));
		add_path_to_blacklist(&black_list, path);
		// In case start-end + some other paths
		if (((t_node*)((t_list*)data->extra->scd)->content)->p == \
				get_node_idx(data, ((t_node*)((t_list*)data->extra->fst)->content)->name))
		{
			dl = 1;
			del_link(data, ((t_node*)((t_list*)data->extra->fst)->content)->name,
					((t_node*)((t_list*)data->extra->scd)->content)->name);
		}
		wash_up_map(data);
		bfs(data, black_list);
		path = NULL;
	}
	// restore deleted link
	if (dl)
		add_link(data, ((t_node*)((t_list*)data->extra->fst)->content)->name,
				((t_node*)((t_list*)data->extra->scd)->content)->name);
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
	else if (rdata->data_type == 0 && !(arr[0] && ft_strchr(arr[0], '-')) &&
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

t_lmdata *read_data(int errors)
{
	t_lmdata	*data;
	char 		*line;
	t_rdata		rdata;
	int			lc;
	int			arr_size;
	int			i;

	lc = 1;
	arr_size = 1;
	i = 0;
	data = NULL;
	init_data(&data, &line, &rdata);
	realloc_arr(&data->input, 0, arr_size);
	rdata.err = read_ants(&data->ants);
	data->input[i++] = ft_itoa(data->ants);
	while (!rdata.err && get_next_line(0, &line))
	{
		parse(&data, &line, &rdata);
		if (i >= arr_size)
		{
			realloc_arr(&data->input, arr_size, arr_size * 2);
			arr_size *= 2;
		}
		if (rdata.err && rdata.err->err_code == ERR_CMD_INV)
		{
			rdata.err = NULL;
			ft_strdel(&line);
			// after writes null
		}
		data->input[i++] = line;
		++lc;
	}
	if (rdata.err)
		rdata.err->line = lc;
	if (rdata.err && rdata.err->err_code == ERR_ROOM_DOUBLE_DEF)
		li_room_double_def(rdata.err, data->input, i);
	if (rdata.err && (rdata.err->err_code == ERR_CMD_DOUBLE_START || rdata.err->err_code == ERR_CMD_DOUBLE_END))
		li_cmd_double(rdata.err, data->input, i);
	if (rdata.err && rdata.err->err_code == ERR_LINK_DOUBLE)
		li_link_double(rdata.err, data->input, i);
	if (!rdata.err && (!data->extra->fst || !data->extra->scd))
		rdata.err = new_err(ERR_PASS_FURTHER, NULL, 0);
	if (rdata.err && rdata.err->err_code == ERR_PASS_FURTHER && !data->extra->fst && !data->extra->scd)
		rdata.err = raise_data_no_start_end();
	else if  (rdata.err && rdata.err->err_code == ERR_PASS_FURTHER && !data->extra->fst)
		rdata.err = raise_data_no_start();
	else if (rdata.err && rdata.err->err_code == ERR_PASS_FURTHER && !data->extra->scd)
		rdata.err = raise_data_no_end();
	data->inp_size = i;
	if (rdata.err)
	{
		error_handler(rdata.err, errors);
		return (NULL);
	}
	return (data);
}

t_list	*get_last_room_with_ant(t_list *path)
{
	while (path)
	{
		if (((t_node *)path->content)->ant != -1)
			break ;
		path = path->next;
	}
	return (path);
}

int		move_ants(t_lmdata *data, t_list *paths, int *al)
{
	int		new;
	int		old;
	t_list	*path;
	int		sm;
	int		spl;

	sm = 0;
	spl = ft_lstlen((t_list *)paths->content);
	while (paths)
	{
		new = 0;
		old = 0;
		path = (t_list *)paths->content;
		if (*al < data->ants && (int)ft_lstlen(path) - spl <= data->ants - *al)
		{
			sm = 1;
			new = ++*al;
			path = path->next;
		}
		while (path)
		{

			old = ((t_node *)path->content)->ant;
			((t_node *)path->content)->ant = 0;
			if (new)
			{
				sm = 1;
				((t_node *)path->content)->ant = new;
				((t_node *)path->content)->fresh = 1;
			}
			new = old;
			path = path->next;
		}
		paths = paths->next;
	}
	return (sm);
}

void	print_ants(t_list *paths)
{
	int		c;
	int		spc;
	t_list	*runner;
	t_list	*path;

	c = 0;
	spc = 0;
	runner = paths;
	while (1)
	{
		ft_lstcorder((t_list **)&runner->content);
		path = (t_list *)runner->content;
		while (path)
		{
			if (((t_node *)path->content)->ant && ((t_node *)path->content)->fresh)
			{
				if (spc)
					ft_putchar(' ');
				ft_printf("L%d-%s", ((t_node *)path->content)->ant, ((t_node *)path->content)->name);
				((t_node *)path->content)->fresh = 0;
				c = 1;
				spc = 1;
				break ;
			}
			path = path->next;
		}
		ft_lstcorder((t_list **)&runner->content);
		runner = runner->next;
		if(!runner && c)
		{
			c = 0;
			runner = paths;
		}
		else if (!runner && !c)
		{
			ft_putchar('\n');
			break ;
		}
	}
}

t_node	*dup_room(t_node *room)
{
	t_node	*new;

	new = (t_node *)ft_memalloc(sizeof(t_node));
	if (new)
	{
		new->x = room->x;
		new->y = room->y;
		new->name = ft_strdup(room->name);
		new->p = room->p;
		new->d = room->d;
		new->visited = room->visited;
		new->ant = room->ant;
		new->fresh = room->fresh;
	}
	return (new);
}

void	full_copy(t_list *paths)
{
	t_list *path;

	while (paths)
	{
		path = (t_list *)paths->content;
		while (path)
		{
			path->content = dup_room((t_node *)path->content);
			path = path->next;
		}
		paths = paths->next;
	}
}

void	make_them_run(t_lmdata *data, t_list *paths)
{
	int		al;

	al = 0;
	while (move_ants(data, paths, &al))
		print_ants(paths);
}

int		main(int argc, char **argv)
{
	int			i;
	int			errors;
	t_list		*paths;
	t_err		*err;
	t_lmdata	*data;

	i = 0;
	err = NULL;
	errors = 0;
	if (argc == 2)
		if (ft_strequ(argv[1], "-e"))
			errors = 1;
	data = read_data(errors);
	if (data)
	{
		if ((paths = get_paths(data)))
		{
			while (i < data->inp_size)
			{
				if (data->input[i])
					ft_printf("%s\n", data->input[i]);
				++i;
			}
			ft_putchar('\n');
			full_copy(paths);
			pdecode_paths(paths);
			make_them_run(data, paths);
		}
		else
		{
			err = raise_data_no_path();
			if (err)
			{
				error_handler(err, errors);
				return (0);
			}
		}
	}
	return (0);
}
