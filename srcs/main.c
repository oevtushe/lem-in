/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:27:51 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/07 11:54:53 by oevtushe         ###   ########.fr       */
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

static int check(void *elem, void *data)
{
	if (ft_strequ((char *)data, ((t_node *)elem)->name))
		return (1);
	return (0);
}

void	del_no_content(void *content, size_t content_size)
{
	content = NULL;
	content_size = 0;
}

/*
** Function find's paths between start and end room
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
		ft_lstappend(&paths, ft_lstnew_cc(path, sizeof(t_list)));
		add_path_to_blacklist(&black_list, path);
		if (((t_node*)((t_list*)data->extra->scd)->content)->p == \
				get_node_idx(data, ((t_node*)((t_list*)data->extra->fst)->content)->name))
		{
			dl = 1;
			del_link(data, ((t_node*)((t_list*)data->extra->fst)->content)->name,
					((t_node*)((t_list*)data->extra->scd)->content)->name);
		}
		wash_up_map(data);
		bfs(data, data->extra->fst, black_list, check);
		// good becase captured by paths
		path = NULL;
	}
	if (dl)
		add_link(data, ((t_node*)((t_list*)data->extra->fst)->content)->name,
				((t_node*)((t_list*)data->extra->scd)->content)->name);
	// black_list contains only pointers on original rooms
	if (black_list)
		ft_lstdel(&black_list, del_no_content);
	return (paths);
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
				if (po->p && ft_lstgetidx((t_list *)extra->fst, ((t_node *)lst->content)->name, cmp_lst_str) != -1 && 
						!ft_strequ(((t_node *)lst->content)->name, ((t_node *)((t_list *)extra->scd)->content)->name))
					ft_printf("%s%sL%d-%s%s", BOLD, GREEN, ((t_node *)lst->content)->ant, ((t_node *)lst->content)->name, RESET);
				else if (po->p && ft_strequ(((t_node *)lst->content)->name, ((t_node *)((t_list *)extra->scd)->content)->name))
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
		po->e = 1;
		res = 1;
	}
	else if (option == 'o')
	{
		po->o = 1;
		res = 1;
	}
	else if (option == 'p')
	{
		po->p = 1;
		res = 1;
	}
	else if (option == 's')
	{
		po->s = 1;
		po->p = 1;
		res = 1;
	}
	return (res);
}

t_list	*wrap_backtracking(t_lmdata *data)
{
	int		bn;
	int		size;
	void	**arr;
	t_pair	pair;
	t_list	*paths;
	t_pair	extra;
	t_pair	roots;

	bn = 0;
	pair.fst = NULL;
	pair.scd = NULL;
	extra.fst = data->extra->fst;
	extra.scd = data->extra->scd;
	roots.fst = ((t_node *)((t_list *)data->extra->fst)->content)->name;
	roots.scd = data->extra->fst;
	backtracking(data, &pair,
			&roots, &bn);
	if (bn == -1)
		return (NULL);
	data->extra->fst = extra.fst;
	data->extra->scd = extra.scd;
	paths = pair.fst;
	print_paths(paths);
	normalize(data, &paths);
	size = ft_lstlen(paths);
	arr = ft_lsttoarr(paths);
	ft_qsarr(arr, 0, size - 1, cmp_len);
	ft_lstdel(&paths, del_empty_node);
	paths = ft_arrtolst(arr, size);
	return (paths);
}

int		cmp_color(void *elem, void *data)
{
	if (*(int *)elem == *(int *)data)
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

/*
** function doesn't clone nodes, just catchs it by pointer 
** don't need to free anything
*/
void	rebase_paths(t_list *paths)
{
	t_path	*p;
	t_list	*colors;
	int		def_one;

	def_one = 196;
	colors = ft_lstnew(&def_one, sizeof(int));
	while (paths)
	{
		p = (t_path *)ft_memalloc(sizeof(t_path));
		p->list = paths->content;
		p->color = gen_color(colors);
		ft_lstadd(&colors, ft_lstnew(&p->color, sizeof(int)));
		paths->content = p;
		paths = paths->next;
	}
	ft_lstdel(&colors, del_int);
}

int		bt_extra_check(t_lmdata *data)
{
	int res;

	res = 0;
	bfs(data, data->extra->fst, NULL, check);
	if (((t_node*)((t_list*)data->extra->scd)->content)->p != \
			get_node_idx(data, ((t_node*)((t_list*)data->extra->fst)->content)->name))
		res = 1;
	wash_up_map(data);
	return (res);
}

void	print_input(char **input, int size, int p)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if (p && input[i])
			ft_printf("\033[38;5;35m%s\033[m\n", input[i]);
		else if (input[i])
			ft_printf("%s\n", input[i]);
		++i;
	}
	ft_putchar('\n');
}

void	mk_output(t_lmdata *data, t_po *po, t_list **paths)
{
	int		*aop;
	int		moves;
	time_t	tm;

	srand((unsigned int)time(&tm));
	rebase_paths(*paths);
	print_input(data->input, data->inp_size, po->p);
	*paths = ft_lstmap(*paths, copy_rebased_paths);
	aop = ft_memalloc(ft_lstlen(*paths) * sizeof(int));
	moves = make_them_run(data, *paths, po, aop);
	if (po->s)
	{
		ft_putchar('\n');
		pdecode_paths(*paths, aop);
		ft_printf("\n%sMoves%s: %d\n", ORANGE, RESET, moves);
	}
}

void	print_usage(void)
{
	ft_printf("Usage: \n"
			"-e -> extended error printing\n"
			"-p -> pretty output\n"
			"-s -> statistics (turns on -p too)\n"
			"-o -> use some kind of optimization for path searching\n");
}

int		main(int argc, char **argv)
{
	t_list		*paths;
	t_err		*err;
	t_lmdata	*data;
	t_po		po;

	paths = NULL;
	err = NULL;
	ft_memset(&po, 0, sizeof(t_po));
	if (argc > 1 && !ft_argsparser(&argv[1], argc - 1, (void *)&po, set_option))
	{
		print_usage();
		return (-42);
	}
	data = read_data(&err);
	if (data)
	{
		if (po.o && bt_extra_check(data))
			paths = wrap_backtracking(data);
		if (!paths)
			paths = get_paths(data);
		if (paths)
			mk_output(data, &po, &paths);
		else
		{
			err = raise_data_no_path();
			error_handler(err, po.e);
			return (-47);
		}
	}
	else
		error_handler(err, po.e);
	return (0);
}
