/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 10:22:44 by oevtushe          #+#    #+#             */
/*   Updated: 2018/06/13 10:25:34 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Function calculates the length of null terminated array of pointers
*/

size_t	ft_arr_len(void **arr)
{
	size_t	len;

	len = 0;
	while (arr[len])
		++len;
	return (len);
}
