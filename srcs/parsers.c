/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 15:57:56 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/10 16:03:21 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	check_arr(void *elem, void *data)
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