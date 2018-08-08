/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 10:44:58 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 16:31:55 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

static int	cmp_color(void *elem, void *data)
{
	if (*(int *)elem == *(int *)data)
		return (1);
	return (0);
}

static int	check_green_level(int color)
{
	if ((color >= 46 && color <= 49) ||
		(color >= 82 && color <= 85) ||
		(color >= 118 && color <= 121) ||
		(color >= 154 && color <= 157) ||
		(color >= 190 && color <= 193))
		return (0);
	return (1);
}

static int	check_shadowy(int color)
{
	if ((color >= 16 && color <= 19) ||
			(color >= 51 && color <= 55) ||
			(color >= 88 && color <= 91) ||
			(color >= 124 && color <= 127))
		return (0);
	return (1);
}

static int	check_red_level(int color)
{
	if ((color >= 160 && color <= 163) ||
			(color >= 196 && color <= 199))
		return (0);
	return (1);
}

int			gen_color(t_list *colors)
{
	int	color;

	color = (rand() % 215) + 16;
	while (ft_lstgetidx(colors, &color, cmp_color) != -1 ||
			!check_green_level(color) ||
			!check_shadowy(color) || !check_red_level(color))
		color = (rand() % 215) + 16;
	return (color);
}
