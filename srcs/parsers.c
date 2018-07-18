/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 15:57:56 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/18 11:17:42 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		parse_command(char *line, int *cmd_mode, t_pair *extra)
{
	int stat;

	stat = 1;
	if (ft_strequ(&line[2], "start"))
	{
		if (!extra->fst && !*cmd_mode)
			*cmd_mode = 1;
		else if (!*cmd_mode)
			stat = ER_CMD_DOUBLE_START;
		else
			stat = ER_CMD_BAD_USING;
	}
	else if (ft_strequ(&line[2], "end"))
	{
		if (!extra->scd && !*cmd_mode)
			*cmd_mode = 2;
		else if (!*cmd_mode)
			stat = ER_CMD_DOUBLE_END;
		else
			stat = ER_CMD_BAD_USING;
	}
	return (stat);
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
	if (arr[0] && ft_strchr(arr[0], '-'))
		return (0);
	if (len != 3)
		return (ER_ROOM_BAD_FORMAT);
	if (arr[0][0] == 'L' || arr[0][0] == '#')
		return (ER_ROOM_BAD_NAME);
	if (!ft_isvldint(arr[1]) || !ft_isvldint(arr[2]))
		return (ER_ROOM_BAD_COORD);
	if (data->adj_cs >= data->adj_as)
		realloc_adj(data);
	if (!ft_arrcontains((void**)data->adj, data->adj_cs, arr[0], check_arr))
	{
		rd = new_node(arr[0], ft_atoi(arr[1]), ft_atoi(arr[2]));
		data->adj[data->adj_cs++] = ft_lstnew(rd, sizeof(t_node));
		res = 1;
		if (cmd_mode == 1)
			extra->fst = data->adj[data->adj_cs - 1];
		else if (cmd_mode == 2)
			extra->scd = data->adj[data->adj_cs - 1];
		ft_memdel((void**)&rd);
	}
	else
		res = ER_ROOM_DOUBLE_DEF;
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
		return (ER_LINK_BAD_FORMAT);
	arr = ft_strsplit(line, '-');
	len = ft_arr_len((void**)arr);
	if (len != 2)
		return (ER_LINK_BAD_FORMAT);
	st1 = ft_strtrim(arr[0]);
	st2 = ft_strtrim(arr[1]);
	if (ft_strchr(st1, ' ') || ft_strchr(st2, ' ') || !*st1 || !*st2)
	{
		ft_strdel(&st1);
		ft_strdel(&st2);
		return (ER_LINK_BAD_FORMAT);
	}
	res = add_link(data, st1, st2);
	ft_free_parr((void***)&arr);
	return (res);
}
