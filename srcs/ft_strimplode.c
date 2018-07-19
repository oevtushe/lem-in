/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strimplode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 15:26:36 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/19 15:46:42 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Function connects all strings in given array 
** using separator into single line
**
** If @param glue is NULL function won't use any 
** separator, just will join the values
**
** If @param arr is NULL function returns NULL 
**
** @param	arr		array values will be connected from
** @param	size	number of strings in the array
** @param	glue	string will be used as separator
** @return			combined string
*/

char *ft_strimplode(char **arr, int size, char *glue)
{
	int		i;
	int		mg;
	char	*res;

	i = 0;
	mg = 0;
	res = NULL;
	if (arr)
	{
		if (!glue)
		{
			glue = ft_strnew(0);
			mg = 1;
		}
		--size;
		while (i < size)
		{
			ft_strconnect(&res, arr[i], 1);
			ft_strconnect(&res, glue, 1);
			++i;
		}
		ft_strconnect(&res, arr[i], 1);
		if (mg)
			ft_strdel(&glue);
	}
	return (res);
}
