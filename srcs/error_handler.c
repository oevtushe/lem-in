/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 12:26:52 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/17 16:26:53 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error_handler(int error)
{
	if (error == 2)
		ft_printf("The room name can't contain 'L' and '#' characters.\n");
	else if (error == 3)
		ft_printf("Bad room format\n");
	else if (error == 4)
		ft_printf("This room already exists\n");
	else if (error == 5)
		ft_printf("Bad coordinates\n");
	else if (error == 6)
		ft_printf("Bad link format\n");
	else if (error == 7)
		ft_printf("Double start definition isn't allowed\n");
	else if (error == 8)
		ft_printf("Double end definition isn't allowed\n");
	else if (error == 9)
		ft_printf("Bad command using\n");
	else if (error == 10)
		ft_printf("Invalid number of ants\n");
}
