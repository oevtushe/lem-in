/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room_hlp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:40:56 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 15:41:09 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_err	*gen_bad_coord_err(char *num1, char *num2)
{
	t_err	*err;

	err = NULL;
	if (!ft_isvldint(num1) && !ft_isvldint(num2))
		err = raise_room_bad_coord(num1, num2);
	else if (!ft_isvldint(num1))
		err = raise_room_bad_x(num1);
	else if (!ft_isvldint(num2))
		err = raise_room_bad_y(num2);
	return (err);
}
