/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:30:20 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/09 09:22:34 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_err	*gen_room_bf_err(char *line, char **arr, int size)
{
	t_err	*err;

	if (size == 1)
		err = raise_room_no_xy(line);
	else if (size == 2)
		err = raise_room_no_y(line);
	else
		err = raise_room_extra_parms(arr, size, line);
	return (err);
}

static int		check_arr(void *elem, void *data)
{
	t_node	*room;

	room = (t_node*)((t_list *)elem)->content;
	if (ft_strequ(room->name, (char *)data))
		return (1);
	return (0);
}

static int		cmp_coords(void *elem, void *data)
{
	t_node	*room;
	char	**arr;

	arr = (char **)data;
	room = (t_node *)((t_list *)elem)->content;
	if (room->x == ft_atoi(arr[0]) && room->y == ft_atoi(arr[1]))
		return (1);
	return (0);
}

static t_err	*check_err_room(char **arr, size_t len,
		char *line, t_lmdata *data)
{
	t_err	*err;

	err = NULL;
	if (len != 3)
		err = gen_room_bf_err(line, arr, len);
	else if (ft_strchcnt(line, ' ') > 2)
		err = raise_room_spaces(line);
	else if (arr[0][0] == 'L')
		err = raise_room_bad_name(line);
	else if (!ft_isvldint(arr[1]) || !ft_isvldint(arr[2]))
		err = gen_bad_coord_err(arr[1], arr[2]);
	else if (ft_arrgetidx((void**)data->adj, data->adj_cs,
				arr[0], check_arr) != -1)
		err = raise_room_double_def(arr[0]);
	else if (ft_arrgetidx((void **)data->adj, data->adj_cs,
				&arr[1], cmp_coords) != -1)
		err = raise_coords_double_def(arr[1], arr[2]);
	return (err);
}

t_err			*parse_room(char *line, t_lmdata *data,
		int cmd_mode, t_pair *extra)
{
	size_t	len;
	char	**arr;
	t_node	*rd;
	t_err	*err;

	err = NULL;
	arr = ft_strsplit(line, ' ');
	len = ft_parrlen_zt((void**)arr);
	if (!(err = check_err_room(arr, len, line, data)))
	{
		if (data->adj_cs >= data->adj_as)
			realloc_adj(data);
		rd = new_node(arr[0], ft_atoi(arr[1]), ft_atoi(arr[2]));
		data->adj[data->adj_cs++] = ft_lstnew(rd, sizeof(t_node));
		if (cmd_mode == 1)
			extra->fst = data->adj[data->adj_cs - 1];
		else if (cmd_mode == 2)
			extra->scd = data->adj[data->adj_cs - 1];
		ft_memdel((void**)&rd);
	}
	ft_parrdel_zt((void***)&arr);
	return (err);
}
