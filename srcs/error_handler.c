/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 12:26:52 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/18 11:13:54 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error_handler(int error)
{
	if (error == ER_ROOM_BAD_NAME)
		ft_printf("Error: The room name can't contain 'L' and '#' characters.\n");
	else if (error == ER_ROOM_BAD_FORMAT)
		ft_printf("Error: Bad room format\n");
	else if (error == ER_ROOM_DOUBLE_DEF)
		ft_printf("Error: This room already exists\n");
	else if (error == ER_ROOM_BAD_COORD)
		ft_printf("Error: Bad coordinates\n");
	else if (error == ER_LINK_BAD_FORMAT)
		ft_printf("Error: Bad link format\n");
	else if (error == ER_CMD_DOUBLE_START)
		ft_printf("Error: Double start definition\n");
	else if (error == ER_CMD_DOUBLE_END)
		ft_printf("Error: Double end definition\n");
	else if (error == ER_CMD_BAD_USING)
		ft_printf("Error: Bad command using\n");
	else if (error == ER_ANTS_INV_NUMBER)
		ft_printf("Error: Invalid number of ants\n");
	else if (error == ER_DATA_EMPTY)
		ft_printf("Error: No input data\n");
	else if (error == ER_DATA_NO_START)
		ft_printf("Error: No start\n");
	else if (error == ER_DATA_NO_END)
		ft_printf("Error: No end\n");
	else if (error == ER_DATA_NO_START_END)
		ft_printf("Error: No start and end\n");
	else if (error == ER_LINK_DOUBLE)
		ft_printf("Error: this nodes are already linked\n");
	else if (error == ER_LINK_SELF)
		ft_printf("Error: selflink\n");
	else if (error == ER_LINK_UNEXISTED_ROOM)
		ft_printf("Error: using unexisted room(s)\n");
}
