/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:27:51 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/12 17:36:14 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "lem_in.h"

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


void	print(t_list *node)
{
	ft_printf("%d\n", *(int*)node->content);
}

void	pdecode_paths(t_lmdata *data, t_list *paths)
{
	t_list *p;

	while (paths)
	{
		p = (t_list *)paths->content;

		ft_printf("%s", ((t_node*)data->adj[*(int*)p->content]->content)->name);
		p = p->next;
		while (p)
		{
			ft_printf("->%s", ((t_node*)data->adj[*(int*)p->content]->content)->name);
			p = p->next;
		}
		paths = paths->next;
		ft_putchar('\n');
	}
}

void	decode_paths(t_list *paths)
{
	t_list *p;

	while (paths)
	{
		p = (t_list *)paths->content;
		ft_printf("\nPath:\n");
		ft_lstiter(p, print);
		paths = paths->next;
	}
}

int		check_overlapping(t_list *paths, t_list *path)
{
	t_list *new_nodes;
	t_list *old_nodes;

	while (paths)
	{
		// ignore end
		old_nodes = ((t_list*)paths->content)->next;
		while (old_nodes)
		{
			// ignore end
			new_nodes = path->next;
			while (new_nodes)
			{
				if (*(int*)old_nodes->content == *(int*)new_nodes->content)
					return (*(int*)old_nodes->content);
				new_nodes = new_nodes->next;
			}
			old_nodes = old_nodes->next;
		}
		paths = paths->next;
	}
	return (-1);
}
/*
void	multipaths(t_lmdata *data, t_pair *extra)
{
	t_list *start;
	t_pair *extra_tmp;
	t_list *paths;
	t_path *path;
	t_list *tmp;
	int		idx;

	paths = NULL;
	idx = 0;
	extra_tmp = ft_memalloc(sizeof(t_pair));
	extra_tmp->scd = extra->scd;
	start = ((t_list*)extra->fst)->next;

	while (start)
	{
		path = ft_memalloc(sizeof(t_path));
		path->black_list = ft_lstnew(&idx, sizeof(int));
		bfs(data, start, path->black_list);
		extra_tmp->fst = start;
		print_path(data, extra_tmp);
		save_path_ro(data, extra_tmp, &path);
		ft_printf("Last common node: %d\n", check_overlapping(paths, path));
		wash_up_map(data);
		start = start->next;
		tmp = ft_lstnew(path, sizeof(t_path));
		ft_lstadd(&paths, tmp);
		ft_memdel((void**)&path);
	}
	decode_paths(paths);
}
*/
int		backtracking(t_lmdata *data, t_list **paths, int root)
{
	int			o;
	int			lo;
	t_list		*path;
	t_source	source;

	path = NULL;
	source.black_list = NULL;
	add_to_blacklist(&source.black_list, root);
	if (!(source.nodes = ((t_list*)data->extra->fst)->next))
		return (-1);
	data->extra->fst = source.nodes;
	wash_up_map(data);
	bfs(data, source.nodes, source.black_list);
	save_path_ro(data, &path);
	print_path(data);
	while (((t_node*)((t_list*)data->extra->scd)->content)->p != 0)
	{
		if ((o = check_overlapping(*paths, path)) != -1)
		{
			ft_printf("overlap: %s\n", ((t_node*)data->adj[o]->content)->name);
			pdecode_paths(data, *paths);
			add_to_blacklist(&source.black_list, o);
		}
		else
		{
			ft_lstadd(paths, ft_lstnew(path, sizeof(t_list)));
			pdecode_paths(data, *paths);
			if ((lo = backtracking(data, paths, root)) == -1)
				return (-1);
			else
			{
				ft_printf("overlap: %s\n", ((t_node*)data->adj[lo]->content)->name);
				*paths = (*paths)->next;
				data->extra->fst = source.nodes;
				add_to_blacklist(&source.black_list, lo);
			}
		}
		path = NULL;
		wash_up_map(data);
		bfs(data, source.nodes, source.black_list);
		print_path(data);
		save_path_ro(data, &path);
	}
	// return first overlap
	return (*(int*)source.black_list->next->content);
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
	t_list		*paths;

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
	data->extra = extra;
#ifdef DEBUG
	pr = 0;
	ft_printf("Result data:\n");
	ft_printf("Source:\n");
	ft_printf("%s\n", ((t_node*)((t_list*)extra->fst)->content)->name);
	ft_printf("Finish:\n");
	ft_printf("%s\n", ((t_node*)((t_list*)extra->scd)->content)->name);
#endif
	//multipaths(data, extra);
	paths = NULL;
	backtracking(data, &paths, 0);
	pdecode_paths(data, paths);
#ifdef DEBUG
	while (pr < data->adj_cs)
	{
		ft_lstiter(data->adj[pr++], print_links);
		ft_putchar('\n');
	}
#endif
	return (0);
}
