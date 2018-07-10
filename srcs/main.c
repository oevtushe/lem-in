/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:27:51 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/09 17:55:05 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "lem_in.h"

void	parse_command(char *line, int *cmd_mode, t_pair *extra)
{
	if (!*cmd_mode)
	{
		if (ft_strequ(&line[2], "start"))
		{
			if (!extra->fst)
			{
				*cmd_mode = 1;
#ifdef DEBUG
				ft_printf("Command: start\n");
#endif
			}
			else
				*cmd_mode = -1;
		}
		else if (ft_strequ(&line[2], "end"))
		{
			if (!extra->scd)
			{
				*cmd_mode = 2;
#ifdef DEBUG
				ft_printf("Command: end\n");
#endif
			}
			else
				*cmd_mode = -1;
		}
#ifdef DEBUG
		else
			ft_printf("Command: unrecognized\n");
#endif
	}
	else
		*cmd_mode = -1;
}

int		check_arr(void *elem, void *data)
{
	t_node	*room;

	room = (t_node*)((t_list *)elem)->content;
	if (ft_strequ(room->name, (char *)data))
		return (1);
	return (0);
}

int		parse_room(char *line, t_lmdata *data, int cmd_mode, t_pair *extra)
{
	size_t	len;
	char	**arr;
	t_node	*rd;
	int		res;

	arr = ft_strsplit(line, ' ');
	len = ft_arr_len((void**)arr);
	res = 0;
	if (len != 3)
		return (0);
	if (arr[0][0] == 'L' || arr[0][0] == '#')
		return (0);
	if (!ft_isvldint(arr[1]) || !ft_isvldint(arr[2]) || ft_strchr(arr[0], '-'))
		return (0);
#ifdef DEBUG
	ft_printf("room_name = %s\n", arr[0]);
	ft_printf("x = %s\n", arr[1]);
	ft_printf("y = %s\n", arr[2]);
#endif
	if (data->adj_cs >= data->adj_as)
	{
		realloc_adj(data);
#ifdef DEBUG
		ft_printf("I'am reallocated\n");
#endif
	}
	if (!ft_arrcontains((void**)data->adj, data->adj_cs, arr[0], check_arr))
	{
		rd = new_node(arr[0], ft_atoi(arr[1]), ft_atoi(arr[2]));
		data->adj[data->adj_cs++] = ft_lstnew(rd, sizeof(t_node));
		res = 1;
#ifdef DEBUG
		ft_printf("Added new room\n");
#endif
		if (cmd_mode == 1)
		{
			extra->fst = data->adj[data->adj_cs - 1];
#ifdef DEBUG
			ft_printf("Start remembered!\n");
#endif
		}
		else if (cmd_mode == 2)
		{
			extra->scd = data->adj[data->adj_cs - 1];
#ifdef DEBUG
			ft_printf("End remembered!\n");
#endif
		}
		ft_memdel((void**)&rd);
	}
#ifdef DEBUG
	else
		ft_printf("This room already exists !\n");
#endif
	ft_free_parr((void***)&arr);
	return (res);
}

int		parse_link(char *line, t_lmdata *data)
{
	size_t	len;
	char	**arr;
	char	*st1;
	char	*st2;
	int		res;

	res = 0;
	len = data->adj_as;
	if (!(st1 = ft_strchr(line, '-')) || ft_strchr(st1 + 1, '-'))
		return (0);
	arr = ft_strsplit(line, '-');
	len = ft_arr_len((void**)arr);
	if (len != 2)
		return (0);
	st1 = ft_strtrim(arr[0]);
	st2 = ft_strtrim(arr[1]);
	if (ft_strchr(st1, ' ') || ft_strchr(st2, ' ') || !*st1 || !*st2)
	{
		ft_strdel(&st1);
		ft_strdel(&st2);
		return (0);
	}
	if (add_link(data, st1, st2))
	{
#ifdef DEBUG
		ft_printf("%s == linked with == %s\n", st1, st2);
#endif
		res = 1;
	}
	ft_free_parr((void***)&arr);
	return (res);
}

int		read_ants(int *ants)
{
	char	*line;
	int		st;

	st = 0;
	line = NULL;
	if (get_next_line(0, &line))
	{
		if (ft_isvldint(line) && line[0] != '-')
		{
			*ants = ft_atoi(line);
			if (*ants)
				st = 1;
		}
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



void	bfs(t_lmdata *data, t_list *start)
{
	t_list	*queue;
	t_node	*u;
	t_list	*v;
	int		idx;

	queue = NULL;
	queue = clone_node(start);
	((t_node *)queue->content)->d = 0;
	while (queue)
	{
		u = ft_lstdequeue(&queue);
		idx = get_node_idx(data, u->name);
		v = data->adj[idx]->next;
		while (v)
		{
			if (!((t_node*)v->content)->visited)
			{
				((t_node*)v->content)->d = u->d + 1;
				((t_node*)v->content)->p = idx;
				ft_lstappend(&queue, clone_node(v));
				((t_node*)v->content)->visited = 1;
			}
			v = v->next;
		}
		u->visited = 1;
	}
}

void	wash_up(t_list *elem)
{
	t_node *node;

	node = (t_node*)elem->content;
	node->d = 0;
	node->p = 0;
	node->visited = 0;
}

void	wash_up_map(t_lmdata *data)
{
	int	i;

	i = 0;
	while (i < data->adj_cs)
		ft_lstiter(data->adj[i++], wash_up);
}

void	print(t_list *node)
{
	ft_printf("%d\n", *(int*)node->content);
}

void	decode_paths(t_list *paths)
{
	t_list *path;

	while (paths)
	{
		path = (t_list *)paths->content;
		ft_printf("\nPath:\n");
		ft_lstiter(path, print);
		paths = paths->next;
	}
}

void	multipaths(t_lmdata *data, t_pair *extra)
{
	t_list *start;
	t_pair *extra_tmp;
	t_list *paths;
	t_path *path;
	t_list *tmp;

	paths = NULL;
	path = NULL;
	extra_tmp = ft_memalloc(sizeof(t_pair));
	extra_tmp->scd = extra->scd;
	start = ((t_list*)extra->fst)->next;
	while (start)
	{
		bfs(data, start);
		extra_tmp->fst = start;
		print_path(data, extra_tmp);
		save_path(data, extra_tmp, &path);
		wash_up_map(data);
		start = start->next;
		tmp = ft_lstnew(path, sizeof(t_list));
		ft_lstadd(&paths, tmp);
		ft_memdel((void**)&path);
	}
	decode_paths(paths);
}

int		main(void)
{
	int			data_type;
	int			cmd_mode;
	char 		*line;
	size_t		len;
	int			pr;
	t_lmdata	*data;
	t_pair		*extra;

	line = NULL;
	cmd_mode = 0;
	data_type = 0;
	len = 0;
	data = new_data(1);
	extra = (t_pair *)ft_memalloc(sizeof(t_pair));
	pr = read_ants(&data->ants);
	while (pr && get_next_line(0, &line))
	{
		len = ft_strlen(line);
		if (len > 1 && line[0] == '#' && line[1] == '#')
			parse_command(line, &cmd_mode, extra);
		else if (len > 0 && line[0] == '#')
		{
			pr = 1;
			ft_printf("It's a comment !\n");
		}
		else if (data_type == 0 && (pr = parse_room(line, data, cmd_mode, extra)))
			cmd_mode = 0;
		else
		{
			if (extra->fst && extra->scd)
			{
				data_type = 1;
				pr = parse_link(line, data);
			}
			else
				pr = 0;
		}
		if (cmd_mode < 0)
			pr = 0;
		ft_strdel(&line);
	}
	if (!pr || !extra->fst || !extra->scd)
	{
		ft_printf("ERROR\n");
		return (1);
	}
#ifdef DEBUG
	pr = 0;
	ft_printf("Result data:\n");
	ft_printf("Source:\n");
	ft_printf("%s\n", ((t_node*)((t_list*)extra->fst)->content)->name);
	ft_printf("Finish:\n");
	ft_printf("%s\n", ((t_node*)((t_list*)extra->scd)->content)->name);
#endif
	multipaths(data, extra);
#ifdef DEBUG
	while (pr < data->adj_cs)
	{
		ft_lstiter(data->adj[pr++], print_links);
		ft_putchar('\n');
	}
#endif
	return (0);
}
