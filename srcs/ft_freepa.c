/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freepa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 18:31:21 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/31 18:49:21 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Function deletes array of pointers with specified size.
** The content of the array may have any type
*/

void	ft_freepa(void ***arr, int size, void (*del)(void *content))
{
	int i;

	i = -1;
	if (arr && *arr)
	{
		while (++i < size)
			if ((*arr)[i])
				del((*arr)[i]);
		ft_memdel((void **)arr);
	}
}
