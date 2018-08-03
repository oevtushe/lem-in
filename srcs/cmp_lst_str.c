/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_lst_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 16:44:11 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/03 15:38:27 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	cmp_lst_str(void *elem, void *data)
{
	if (ft_strequ(((t_node *)elem)->name, (char *)data))
		return (1);
	return (0);
}
