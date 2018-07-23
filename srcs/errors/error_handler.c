/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 12:26:52 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/23 11:29:23 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_err_dsp	*new_dsp_entry(int err_code, char *(*err_handler)(void **, int))
{
	t_err_dsp *entry;

	entry = (t_err_dsp*)ft_memalloc(sizeof(t_err_dsp));
	if (entry)
	{
		entry->err_code = err_code;
		entry->err_handler = err_handler;
	}
	return (entry);
}

t_err_dsp	**init_dsp(void)
{
	t_err_dsp **dsp;

	dsp = (t_err_dsp **)ft_memalloc(sizeof(t_err_dsp*) * DSP_SIZE);
	dsp[0] = new_dsp_entry(ERR_ROOM_BAD_NAME, hlr_room_bad_name);
	dsp[1] = new_dsp_entry(ERR_ROOM_DOUBLE_DEF, hlr_room_double_def);
	dsp[2] = new_dsp_entry(ERR_ROOM_BAD_COORD, hlr_room_bad_coord);
	dsp[3] = new_dsp_entry(ERR_ROOM_BAD_X, hlr_room_bad_x);
	dsp[4] = new_dsp_entry(ERR_ROOM_BAD_Y, hlr_room_bad_y);
	dsp[5] = new_dsp_entry(ERR_ROOM_NO_XY, hlr_room_no_xy);
	dsp[6] = new_dsp_entry(ERR_ROOM_NO_Y, hlr_room_no_y);
	dsp[7] = new_dsp_entry(ERR_ROOM_EXTRA_PARMS, hlr_room_extra_parms);
	dsp[8] = new_dsp_entry(ERR_ROOM_EXTRA_PARMS, hlr_room_extra_parms);
	dsp[9] = new_dsp_entry(ERR_LINK_EXTRA_LINK_CHRS, hlr_link_extra_link_chrs);
	dsp[10] = new_dsp_entry(ERR_LINK_SELF, hlr_link_self);
	dsp[11] = new_dsp_entry(ERR_LINK_DOUBLE, hlr_link_double);
	dsp[12] = new_dsp_entry(ERR_LINK_UNS_DATA, hlr_link_uns_data);
	dsp[13] = new_dsp_entry(ERR_LINK_SPACES, hlr_link_spaces);
	dsp[14] = new_dsp_entry(ERR_LINK_NOT_EXISTING_ROOM, hlr_link_not_existing_room);
	dsp[15] = new_dsp_entry(ERR_CMD_DOUBLE_START, hlr_cmd_double_start);
	dsp[16] = new_dsp_entry(ERR_CMD_DOUBLE_END, hlr_cmd_double_end);
	dsp[17] = new_dsp_entry(ERR_CMD_BAD_USING, hlr_cmd_bad_using);
	dsp[18] = new_dsp_entry(ERR_DATA_EMPTY, hlr_data_empty);
	dsp[19] = new_dsp_entry(ERR_DATA_NO_START, hlr_data_no_start);
	dsp[20] = new_dsp_entry(ERR_DATA_NO_END, hlr_data_no_end);
	dsp[21] = new_dsp_entry(ERR_DATA_NO_START_END, hlr_data_no_start_end);
	dsp[22] = new_dsp_entry(ERR_ANTS_INV_NUMBER, hlr_ants_inv_number);
	return (dsp);
}

void	error_handler(t_err *err)
{
	int			i;
	char		*err_msg;
	t_err_dsp	**dsp;

	i = 0;
	err_msg = NULL;
	dsp = init_dsp();
	while (i < DSP_SIZE)
	{
		if (dsp[i]->err_code == err->err_code)
		{
			err_msg = dsp[i]->err_handler(&err->extra, err->line);
			break ;
		}
		++i;
	}
	if (err_msg)
		ft_putstr_fd(err_msg, 2);
}
