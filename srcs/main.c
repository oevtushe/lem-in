/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:27:51 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/03 11:55:40 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "lem_in.h"
#include <stdlib.h>
#include <time.h>

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
		if (st != ERR_NONE)
			err = raise_ants_inv_num(line);
		ft_strdel(&line);
	}
	if (!err && st == ERR_DATA_EMPTY)
		err = raise_data_empty();
	return (err);
}

static int check(t_list *elem, void *data)
{
	if (ft_strequ((char *)data, ((t_node *)elem->content)->name))
		return (1);
	return (0);
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
	bfs(data, data->extra->fst, black_list, check);
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
		bfs(data, data->extra->fst, black_list, check);
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
	{
		if (rdata->cmd_mode)
			rdata->err = raise_cmnt_after_cmd(*line);
		return ;
	}
	else if (rdata->data_type == 0 && arr[0] && !ft_strchr(arr[0], '-') &&
			!(rdata->err = parse_room(*line, *data, rdata->cmd_mode, (*data)->extra)))
		rdata->cmd_mode = 0;
	else if (!rdata->err && (*data)->extra->fst && (*data)->extra->scd)
	{
		rdata->data_type = 1;
		rdata->err = parse_link(*line, *data);
	}
	else if (!rdata->err && rdata->cmd_mode)
		rdata->err = raise_cmd_bad_using(*line);
	else if (!rdata->err)
		rdata->err = new_err(ERR_PASS_FURTHER, NULL, 0);
}

void		li_handler(t_err *err, char **input, int i)
{
	if (err->err_code == ERR_ROOM_DOUBLE_DEF)
		li_room_double_def(err, input, i);
	else if ((err->err_code == ERR_CMD_DOUBLE_START
				|| err->err_code == ERR_CMD_DOUBLE_END))
		li_cmd_double(err, input, i);
	else if (err->err_code == ERR_LINK_DOUBLE)
		li_link_double(err, input, i);
	else if (err->err_code == ERR_COORDS_DOUBLE_DEF)
		li_coords_double_def(err, input, i);
}

void	further_handlers(t_err **err, t_pair *extra)
{
	if (!extra->fst && !extra->scd)
		*err = raise_data_no_start_end();
	else if  (!extra->fst)
		*err = raise_data_no_start();
	else if (!extra->scd)
		*err = raise_data_no_end();
}

void	do_err(t_err **err, t_lmdata *data, int i, int oerrs)
{
	if (*err)
	{
		(*err)->line = i;
		li_handler(*err, data->input, i);
	}
	if (!*err && (!data->extra->fst || !data->extra->scd))
		*err = new_err(ERR_PASS_FURTHER, NULL, 0);
	if (*err && (*err)->err_code == ERR_PASS_FURTHER)
		further_handlers(err, data->extra);
	error_handler(*err, oerrs);
}

void	free_adj(void *content)
{
	t_node *node;

	node = (t_node *)(((t_list *)content)->content);
	ft_strdel(&node->name);
}

t_lmdata *read_data(int errors)
{
	t_lmdata	*data;
	char 		*line;
	t_rdata		rdata;
	int			arr_size;
	int			i;

	i = 0;
	data = NULL;
	arr_size = 1;
	init_data(&data, &line, &rdata);
	ft_realloc((void **)&data->input, 0, sizeof(void *) * arr_size);
	rdata.err = read_ants(&data->ants);
	data->input[i++] = ft_itoa(data->ants);
	while (!rdata.err && get_next_line(0, &line))
	{
		if (!ft_strlen(line))
			rdata.err = raise_empty_line();
		else
			parse(&data, &line, &rdata);
		if (i >= arr_size)
			realloc_input(&data->input, &arr_size);
		if (rdata.err && rdata.err->err_code == ERR_CMD_INV)
		{
			if (rdata.cmd_mode)
				rdata.err = raise_cmd_bad_using(line);
			else
			{
				rdata.err = NULL;
				ft_strdel(&line);
			}
		}
		data->input[i++] = line;
	}
	data->inp_size = i;
	ft_realloc((void **)&data->input, i * sizeof(void *), i * sizeof(void *));
	if (rdata.err || !data->extra->fst || !data->extra->scd)
	{
		do_err(&rdata.err, data, i, errors);
		ft_freepa_sd((void ***)&data->input, data->inp_size);
		ft_freepa((void ***)&data->adj, data->adj_cs, free_adj);
		ft_memdel((void **)&data->extra);
		ft_memdel((void **)&data);
	}
	return (data);
}

int		move_ants(t_lmdata *data, t_list *paths, int *al, int *aop)
{
	int		i;
	int		new;
	int		old;
	t_list	*path;
	int		sm;
	int		spl;

	i = 0;
	sm = 0;
	spl = ft_lstlen(((t_path *)paths->content)->list);
	while (paths)
	{
		new = 0;
		old = 0;
		path = ((t_path *)paths->content)->list;
		if (*al < data->ants && (int)ft_lstlen(path) - spl <= data->ants - *al)
		{
			++aop[i];
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
		++i;
	}
	return (sm);
}

/*
** Function cycles through the paths list and prints moved ants in the following
** order:
**			first ant moved on the first path
**			first ant moved on the second path
**			...
**			second ant moved on the first path
**			second ant moved on the second path
**			...
**
** ('first' && 'second') is about the last(the closest one
** to the end) ant on the current path.
** Continue until there is at least one moved ant in the paths list
*/

void	print_ants(t_list *paths, t_pair *extra, t_po *po)
{
	int		c;
	int		spc;
	t_list	*runner;
	t_path	*path;
	t_list	*lst;

	c = 0;
	spc = 0;
	runner = paths;
	while (1)
	{
		ft_lstcorder(&((t_path *)runner->content)->list);
		path = (t_path *)runner->content;
		lst = path->list;
		while (lst)
		{
			if (((t_node *)lst->content)->ant && ((t_node *)lst->content)->fresh)
			{
				if (spc)
					ft_putchar(' ');
				if (po->h && ft_lstgetidx((t_list *)extra->fst, ((t_node *)lst->content)->name, cmp_lst_str) != -1 && 
						!ft_strequ(((t_node *)lst->content)->name, ((t_node *)((t_list *)extra->scd)->content)->name))
					ft_printf("%s%sL%d-%s%s", BOLD, GREEN, ((t_node *)lst->content)->ant, ((t_node *)lst->content)->name, RESET);
				else if (po->h && ft_strequ(((t_node *)lst->content)->name, ((t_node *)((t_list *)extra->scd)->content)->name))
					ft_printf("%s\033[38;5;196mL%d-%s\033[m", BOLD, ((t_node *)lst->content)->ant, ((t_node *)lst->content)->name);
				else
					ft_printf("\033[38;5;%dmL%d-%s\033[m", path->color, ((t_node *)lst->content)->ant, ((t_node *)lst->content)->name);
				((t_node *)lst->content)->fresh = 0;
				c = 1;
				spc = 1;
				break ;
			}
			lst = lst->next;
		}
		ft_lstcorder(&((t_path *)runner->content)->list);
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
	t_path	*pn;
	t_path	*p;
	t_list	*lst;

	while (paths)
	{
		p = (t_path *)paths->content;
		pn = ft_memalloc(sizeof(t_path));
		pn->list = p->list;
		pn->color = p->color;
		paths->content = pn;
		lst = pn->list;
		while (lst)
		{
			lst->content = dup_room((t_node *)lst->content);
			lst = lst->next;
		}
		paths = paths->next;
	}
}

int		make_them_run(t_lmdata *data, t_list *paths, t_po *po, int *aop)
{
	int		al;
	int		moves;

	al = 0;
	moves = 0;
	while (move_ants(data, paths, &al, aop))
	{
		print_ants(paths, data->extra, po);
		++moves;
	}
	return (moves);
}

void	normalize(t_lmdata *data, t_list **paths)
{
	t_list	*n;
	int		idx;
	t_list	*r;

	r = *paths;
	idx = get_node_idx(data, ((t_node *)((t_list *)data->extra->fst)->content)->name);
	while (r)
	{
		ft_lstcorder((t_list **)&r->content);
		n = clone_node(data->adj[idx]);
		ft_lstadd((t_list **)&r->content, n);
		r = r->next;
	}
	ft_lstcorder(paths);
}

int		cmp_len(void *a, void *b)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_lstlen((t_list *)a);
	len2 = ft_lstlen((t_list *)b);
	if (len1 > len2)
		return (1);
	else if (len1 < len2)
		return (-1);
	return (0);
}

int		set_option(void *container, char option)
{
	t_po	*po;
	int		res;

	res = 0;
	po = (t_po *)container;
	if (option == 'e')
	{
		po->errors = 1;
		res = 1;
	}
	else if (option == 'o')
	{
		po->bt = 1;
		res = 1;
	}
	else if (option == 'p')
	{
		po->h = 1;
		res = 1;
	}
	else if (option == 's')
	{
		po->s = 1;
		po->h = 1;
		res = 1;
	}
	return (res);
}

t_list	*wrap_backtracking(t_lmdata *data)
{
	t_pair	pair;
	void	**arr;
	t_list	*paths;
	t_pair	extra;
	int		size;
	int		bn;

	bn = 0;
	pair.fst = NULL;
	pair.scd = NULL;
	extra.fst = data->extra->fst;
	extra.scd = data->extra->scd;
	backtracking(data, &pair,
			((t_node *)((t_list *)data->extra->fst)->content)->name, &bn);
	if (bn == -1)
		return (NULL);
	data->extra->fst = extra.fst;
	data->extra->scd = extra.scd;
	paths = pair.fst;
	normalize(data, &paths);

	size = ft_lstlen(paths);
	arr = ft_lsttoarr(paths);
	ft_qsarr(arr, 0, size - 1, cmp_len);
	ft_lstdel(&paths, del_empty_node);
	paths = ft_arrtolst(arr, size);
	return (paths);
}

int		cmp_color(t_list *elem, void *data)
{
	if (*(int *)elem->content == *(int *)data)
		return (1);
	return (0);
}

int		check_green_level(int color)
{
	if ((color >= 46 && color <= 49) ||
		(color >= 82 && color <= 85) ||
		(color >= 118 && color <= 121) ||
		(color >= 154 && color <= 157) ||
		(color >= 190 && color <= 193))
		return (0);
	return (1);
}

int		check_shadowy(int color)
{
	if ((color >= 16 && color <= 19) ||
			(color >= 51 && color <= 55) ||
			(color >= 88 && color <= 91) ||
			(color >= 124 && color <= 127))
		return (0);
	return (1);
}

int		check_red_level(int color)
{
	if ((color >= 160 && color <= 163) ||
			(color >= 196 && color <= 199))
		return (0);
	return (1);
}

int		gen_color(t_list *colors)
{
	int	color;

	color = (rand() % 215) + 16;
	while (ft_lstgetidx(colors, &color, cmp_color) != -1 || !check_green_level(color) ||
			!check_shadowy(color) || !check_red_level(color))
		color = (rand() % 215) + 16;
	return (color);
}

void	rebase_one(t_list *paths)
{
	t_path	*p;
	t_list	*colors;
	int		def_one;

	def_one = 125;
	colors = ft_lstnew(&def_one, sizeof(int));
	while (paths)
	{
		p = ft_memalloc(sizeof(t_path));
		p->list = paths->content;
		p->color = gen_color(colors);
		paths->content = p;
		paths = paths->next;
	}
}

int		main(int argc, char **argv)
{
	int			i;
	t_list		*paths;
	t_err		*err;
	t_lmdata	*data;
	t_po		po;
	int			*aop;
	int			moves;

	i = 0;
	paths = NULL;
	err = NULL;
	po.errors = 0;
	po.bt = 0;
	if (argc > 1 && !ft_argsparser(&argv[1], argc - 1, (void *)&po, set_option))
	{
		ft_printf("Usage: \n-o -> use some kind of optimization for path searching\n"
				"-e -> extended error printing\n"
				"-p -> pretty output\n"
				"-s -> statistics (turns on -p too)\n");
		return (-42);
	}
	data = read_data(po.errors);
	if (data)
	{
		if (po.bt)
			paths = wrap_backtracking(data);
		if (!paths)
			paths = get_paths(data);
		time_t tm;

		srand((unsigned int)time(&tm));
		rebase_one(paths);
		if (paths)
		{
			while (i < data->inp_size)
			{
				if (po.h && data->input[i])
					ft_printf("\033[38;5;35m%s\033[m\n", data->input[i]);
				else
					ft_printf("%s\n", data->input[i]);
				++i;
			}
			ft_putchar('\n');
			full_copy(paths);
			aop = ft_memalloc(ft_lstlen(paths) * sizeof(int));
			moves = make_them_run(data, paths, &po, aop);
			if (po.s)
			{
				ft_putchar('\n');
				pdecode_paths(paths, aop);
				ft_printf("\n%sMoves%s: %d\n", ORANGE, RESET, moves);
			}
		}
		else
		{
			err = raise_data_no_path();
			if (err)
			{
				error_handler(err, po.errors);
				return (0);
			}
		}
	}
	return (0);
}
