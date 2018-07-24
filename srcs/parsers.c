/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 15:57:56 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/24 10:46:59 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_err	*parse_command(char *line, int *cmd_mode, t_pair *extra)
{
	t_err	*err;

	err = NULL;
	if (ft_strequ(&line[2], "start"))
	{
		if (!extra->fst && !*cmd_mode)
			*cmd_mode = 1;
		else if (!*cmd_mode)
			err = raise_cmd_double_start();
		else
			err = raise_cmd_bad_using();
	}
	else if (ft_strequ(&line[2], "end"))
	{
		if (!extra->scd && !*cmd_mode)
			*cmd_mode = 2;
		else if (!*cmd_mode)
			err = raise_cmd_double_end();
		else
			err = raise_cmd_bad_using();
	}
	else
		err = new_err(ERR_CMD_INV, NULL, 0);
	return (err);
}

static int	check_arr(void *elem, void *data)
{
	t_node	*room;

	room = (t_node*)((t_list *)elem)->content;
	if (ft_strequ(room->name, (char *)data))
		return (1);
	return (0);
}

static t_err *gen_room_bf_err(char *line, char **arr, int size)
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

static t_err	*gen_bad_coord_err(char *num1, char *num2)
{
	t_err	*err;

	err = NULL;
	if (!ft_isvldint(num1) && !ft_isvldint(num2))
		err = raise_room_bad_coord(num1, num2);
	else if (!ft_isvldint(num1))
		err = raise_room_bad_x(num1);
	else if (!ft_isvldint(num2))
		err = raise_room_bad_y(num1);
	return (err);
}

t_err		*parse_room(char *line, t_lmdata *data, int cmd_mode, t_pair *extra)
{
	size_t	len;
	char	**arr;
	t_node	*rd;
	t_err	*err;

	err = NULL;
	arr = ft_strsplit(line, ' ');
	len = ft_parrlen_zt((void**)arr);
	if (len != 3)
	{
		err = gen_room_bf_err(line, arr, len);
		return (err);
	}
	if (ft_strchcnt(line, ' ') > 2)
	{
		err = raise_room_spaces(line);
		return (err);
	}
	if (arr[0][0] == 'L')
	{
		err = raise_room_bad_name(line);
		return (err);
	}
	if (!ft_isvldint(arr[1]) || !ft_isvldint(arr[2]))
	{
		err = gen_bad_coord_err(arr[1], arr[2]);
		return (err);
	}
	if (data->adj_cs >= data->adj_as)
		realloc_adj(data);
	if (!ft_arrcontains((void**)data->adj, data->adj_cs, arr[0], check_arr))
	{
		rd = new_node(arr[0], ft_atoi(arr[1]), ft_atoi(arr[2]));
		data->adj[data->adj_cs++] = ft_lstnew(rd, sizeof(t_node));
		if (cmd_mode == 1)
			extra->fst = data->adj[data->adj_cs - 1];
		else if (cmd_mode == 2)
			extra->scd = data->adj[data->adj_cs - 1];
		ft_memdel((void**)&rd);
	}
	else
		err = raise_room_double_def(arr[0]);
	ft_parrdel_zt((void***)&arr);
	return (err);
}

t_err		*parse_link(char *line, t_lmdata *data)
{
	size_t	len;
	char	**arr;
	t_err	*err;
	char	*tmp;

	err = NULL;
	len = data->adj_as;
	if ((tmp = ft_strchr(line, '-')) && ft_strchr(tmp + 1, '-'))
	{
		err = raise_link_extra_link_chrs(line);
		return (err);
	}
	arr = ft_strsplit(line, '-');
	len = ft_parrlen_zt((void**)arr);
	if (len != 2)
	{
		err = raise_link_uns_data(line);
		return (err);
	}
	if (ft_strchr(arr[0], ' ') || ft_strchr(arr[1], ' '))
	{
		err = raise_link_spaces(line, arr[0], arr[1]);
		return (err);
	}
	err = add_link(data, arr[0], arr[1]);
	ft_parrdel_zt((void***)&arr);
	return (err);
}
