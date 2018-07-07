/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrcontains.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 11:42:33 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/05 11:50:59 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_arrcontains(void **arr, int size, void *data, int (*check)(void *elem, void *data))
{
	int i;

	i = 0;
	while (i < size)
		if (check(arr[i++], data))
			return (1);
	return (0);
}
