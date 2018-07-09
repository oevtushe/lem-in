/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:27:51 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/07 20:00:11 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "lem_in.h"

void	parse_command(char *line, int *cmd_mode)
{
	if (!*cmd_mode)
	{
		if (ft_strequ(&line[2], "start"))
		{
			*cmd_mode = 1;
			ft_printf("Command: start\n");
		}
		else if (ft_strequ(&line[2], "end"))
		{
			*cmd_mode = 2;
			ft_printf("Command: end\n");
		}
		else
			ft_printf("Command: unrecognized\n");
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
	ft_printf("room_name = %s\n", arr[0]);
	ft_printf("x = %s\n", arr[1]);
	ft_printf("y = %s\n", arr[2]);
	if (data->adj_cs >= data->adj_as)
	{
		realloc_adj(data);
		ft_printf("I'am reallocated\n");
	}
	if (!ft_arrcontains((void**)data->adj, data->adj_cs, arr[0], check_arr))
	{
		rd = new_node(arr[0], ft_atoi(arr[1]), ft_atoi(arr[2]));
		data->adj[data->adj_cs++] = ft_lstnew(rd, sizeof(t_node));
		res = 1;
		ft_printf("Added new room\n");
		if (cmd_mode == 1)
		{
			extra->fst = data->adj[data->adj_cs - 1];
			ft_printf("Start remembered!\n");
		}
		else if (cmd_mode == 2)
		{
			extra->scd = data->adj[data->adj_cs - 1];
			ft_printf("End remembered!\n");
		}
		ft_memdel((void**)&rd);
	}
	else
		ft_printf("This room already exists !\n");
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
		ft_printf("%s == linked with == %s\n", st1, st2);
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

void	bfs(t_lmdata *data, t_pair *extra)
{
	t_list	*queue;
	t_node	*u;
	t_list	*v;
	int		idx;

	queue = NULL;
	queue = clone_node(extra->fst);
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

void	print_path(t_lmdata *data, t_pair *extra)
{
	t_node *cur;
	t_node *start;
	t_node *end;

	start = (t_node*)((t_list*)extra->fst)->content; 
	end = (t_node*)((t_list*)extra->scd)->content; 
	cur = end;
	while (cur->name != start->name)
	{
		ft_printf("%s->", cur->name);
		cur = (t_node *)data->adj[cur->p]->content;
	}
	ft_printf("%s\n", cur->name);
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
			parse_command(line, &cmd_mode);
		else if (len > 0 && line[0] == '#')
		{
			pr = 1;
			ft_printf("It's a comment !\n");
		}
		else if (data_type == 0 && (pr = parse_room(line, data, cmd_mode, extra)))
		{
			cmd_mode = 0;
		}
		else
		{
			data_type = 1;
			pr = parse_link(line, data);
		}
		if (!pr || cmd_mode < 0)
			pr = 0;
		ft_strdel(&line);
	}
	if (!pr || !extra->fst || !extra->scd)
	{
		ft_printf("ERROR\n");
		return (0);
	}
	pr = 0;
	ft_printf("Result data:\n");
	ft_printf("Source:\n");
	ft_printf("%s\n", ((t_node*)((t_list*)extra->fst)->content)->name);
	ft_printf("Finish:\n");
	ft_printf("%s\n", ((t_node*)((t_list*)extra->scd)->content)->name);
	bfs(data, extra);
#ifdef DEBUG
	while (pr < data->adj_cs)
	{
		ft_lstiter(data->adj[pr++], print_links);
		ft_putchar('\n');
	}
#endif
	print_path(data, extra);
	return (0);
}
