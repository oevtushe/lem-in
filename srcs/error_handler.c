/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 12:26:52 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/14 13:03:16 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error_handler(int error)
{
	if (error == 2)
		ft_printf("The room name can't contain 'L' and '#' characters.\n");
	else if (error == 3)
		ft_printf("Wrong room specification.\nRoom format: <room_name> <x> <y>\n");
	else if (error == 4)
		ft_printf("This room already exists\n");
	else if (error == 5)
		ft_printf("Bad coordinates\n");
	else if (error == 6)
		ft_printf("Wrong link format.\nFormat: <name1>-<name2>\n");
}
