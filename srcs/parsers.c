/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 15:57:56 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 16:37:33 by oevtushe         ###   ########.fr       */
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
			err = raise_cmd_bad_using(line);
	}
	else if (ft_strequ(&line[2], "end"))
	{
		if (!extra->scd && !*cmd_mode)
			*cmd_mode = 2;
		else if (!*cmd_mode)
			err = raise_cmd_double_end();
		else
			err = raise_cmd_bad_using(line);
	}
	else
		err = new_err(ERR_CMD_INV, NULL, 0);
	return (err);
}

t_err	*parse_link(char *line, t_lmdata *data)
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
		err = raise_link_uns_data(line);
	else if (ft_strchr(arr[0], ' ') || ft_strchr(arr[1], ' '))
		err = raise_link_spaces(line, arr[0], arr[1]);
	else
		err = add_link(data, arr[0], arr[1]);
	ft_parrdel_zt((void***)&arr);
	return (err);
}
