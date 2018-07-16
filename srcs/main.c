/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:27:51 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/14 12:58:16 by oevtushe         ###   ########.fr       */
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

int		main(void)
{
	int			data_type;
	int			cmd_mode;
	char 		*line;
	size_t		len;
	int			pr;
	t_lmdata	*data;
	t_pair		*extra;
	t_pair		*paths;

	line = NULL;
	cmd_mode = 0;
	data_type = 0;
	len = 0;
	data = new_data(1);
	extra = (t_pair *)ft_memalloc(sizeof(t_pair));
	pr = read_ants(&data->ants);
	while (pr == 1 && get_next_line(0, &line))
	{
		len = ft_strlen(line);
		if (data_type == 0 && len > 1 && line[0] == '#' && line[1] == '#')
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
	if (pr != 1 || !extra->fst || !extra->scd)
	{
		ft_printf("%d\n", pr);
		error_handler(pr);
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
	paths = ft_memalloc(sizeof(t_pair));
	int res;
	res = backtracking(data, paths, 0);
	pdecode_paths(data, (t_list*)paths->fst);
#ifdef DEBUG
	while (pr < data->adj_cs)
	{
		ft_lstiter(data->adj[pr++], print_links);
		ft_putchar('\n');
	}
#endif
	return (0);
}
