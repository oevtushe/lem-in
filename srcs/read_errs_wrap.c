/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_errs_wrap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 18:15:57 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/09 10:39:56 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	further_handlers(t_err **err, t_pair *extra)
{
	ft_memdel((void **)err);
	if (!extra->fst && !extra->scd)
		*err = raise_data_no_start_end();
	else if (!extra->fst)
		*err = raise_data_no_start();
	else if (!extra->scd)
		*err = raise_data_no_end();
}

void	li_handler(t_err *err, char **input, int size)
{
	if (err->err_code == ERR_ROOM_DOUBLE_DEF)
		li_room_double_def(err, input, size);
	else if ((err->err_code == ERR_CMD_DOUBLE_START
				|| err->err_code == ERR_CMD_DOUBLE_END))
		li_cmd_double(err, input, size);
	else if (err->err_code == ERR_LINK_DOUBLE)
		li_link_double(err, input, size);
	else if (err->err_code == ERR_COORDS_DOUBLE_DEF)
		li_coords_double_def(err, input, size);
}

void	do_cmd_inv(int cmd_mode, char **line, t_err **err)
{
	ft_memdel((void **)err);
	if (cmd_mode)
		*err = raise_cmd_bad_using(*line);
	else
	{
		ft_memdel((void **)err);
		ft_strdel(line);
	}
}

void	do_err(t_err **err, t_lmdata *data, int i)
{
	if (*err)
	{
		(*err)->line = i;
		li_handler(*err, data->input, i);
	}
	if (!*err && (!data->extra->fst || !data->extra->scd))
		*err = new_err(ERR_PASS_FURTHER, NULL, 0);
	if (*err && (*err)->err_code == ERR_PASS_FURTHER)
		further_handlers(err, data->extra);
}
