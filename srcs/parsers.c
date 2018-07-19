/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 15:57:56 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/19 18:43:30 by oevtushe         ###   ########.fr       */
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
			err = new_err(ER_CMD_DOUBLE_START, NULL, 0);
		else
			err = new_err(ER_CMD_BAD_USING, NULL, 0);
	}
	else if (ft_strequ(&line[2], "end"))
	{
		if (!extra->scd && !*cmd_mode)
			*cmd_mode = 2;
		else if (!*cmd_mode)
			err = new_err(ER_CMD_DOUBLE_END, NULL, 0);
		else
			err = new_err(ER_CMD_BAD_USING, NULL, 0);
	}
	else
		err = new_err(ER_CMD_INV, NULL, 0);
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
	t_pair	*pair;
	char	*imploded;

	pair = NULL;
	imploded = NULL;
	if (size == 1)
		err = new_err(ER_ROOM_NO_XY, line, ft_strlen(line) + 1);
	else if (size == 2)
		err = new_err(ER_ROOM_NO_Y, line, ft_strlen(line) + 1);
	else
	{
		imploded = ft_strimplode(&arr[3], size - 3, " ");
		pair = ft_newpair(line, ft_strlen(line) + 1, imploded, ft_strlen(imploded) + 1);
		err = new_err(ER_ROOM_EXTRA_PARMS, pair, sizeof(t_pair));
		ft_strdel(&imploded);
		ft_memdel((void**)&pair);
	}
	return (err);
}

static t_err	*gen_bad_coord_err(char *num1, char *num2)
{
	t_err	*err;
	t_pair *pair;

	err = NULL;
	if (!ft_isvldint(num1) && !ft_isvldint(num2))
	{
		pair = ft_newpair(num1, ft_strlen(num1) + 1, num2, ft_strlen(num2) + 1);
		err = new_err(ER_ROOM_BAD_COORD, pair, sizeof(t_pair));
		ft_memdel((void**)&pair);
	}
	else if (!ft_isvldint(num1))
		err = new_err(ER_ROOM_BAD_X, num1, ft_strlen(num1) + 1);
	else if (!ft_isvldint(num2))
		err = new_err(ER_ROOM_BAD_Y, num2, ft_strlen(num2) + 1);
	return (err);
}

t_err		*parse_room(char *line, t_lmdata *data, int cmd_mode, t_pair *extra)
{
	size_t	len;
	char	**arr;
	t_node	*rd;
	int		res;
	t_err	*err;

	err = NULL;
	arr = ft_strsplit(line, ' ');
	len = ft_arr_len((void**)arr);
	if (len != 3)
	{
		err = gen_room_bf_err(line, arr, len);
		return (err);
	}
	if (arr[0][0] == 'L')
	{
		err = new_err(ER_ROOM_BAD_NAME, line, ft_strlen(line) + 1);
		return (err);
	}
	if (!ft_isvldint(arr[1]) || !ft_isvldint(arr[2]))
	{
		// Define which coordinate is bad and why
		err = gen_bad_coord_err(arr[1], arr[2]);
		return (err);
	}
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
		err = new_err(ER_ROOM_DOUBLE_DEF, arr[0], ft_strlen(arr[0]) + 1);
	ft_free_parr((void***)&arr);
	return (err);
}

static t_err	*gen_spaces_err(char *line, char *st1, char *st2)
{
	t_err	*err;

	err = NULL;
	if (ft_strchr(st1, ' '))
		err = new_err(ER_LINK_SPACES, st1, ft_strlen(st1) + 1);
	else if (ft_strchr(st2, ' '))
		err = new_err(ER_LINK_SPACES, st2, ft_strlen(st2) + 1);
	else
		err = new_err(ER_LINK_SPACES, line, ft_strlen(line) + 1);
	return (err);
}

t_err		*parse_link(char *line, t_lmdata *data)
{
	size_t	len;
	char	**arr;
	int		res;
	t_err	*err;
	char	*tmp;

	res = 0;
	err = NULL;
	len = data->adj_as;
	if ((tmp = ft_strchr(line, '-')) && ft_strchr(tmp + 1, '-'))
	{
		err = new_err(ER_LINK_EXTRA_LINK_CHRS, line, ft_strlen(line) + 1);
		return (err);
	}
	arr = ft_strsplit(line, '-');
	len = ft_arr_len((void**)arr);
	if (len != 2)
	{
		err = new_err(ER_LINK_UNS_DATA, line, ft_strlen(line) + 1);
		return (err);
	}
	if (ft_strchr(arr[0], ' ') || ft_strchr(arr[1], ' '))
	{
		err = gen_spaces_err(line, arr[0], arr[1]);
		return (err);
	}
	err = add_link(data, arr[0], arr[1]);
	ft_free_parr((void***)&arr);
	return (err);
}
