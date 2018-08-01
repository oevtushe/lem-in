/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsarr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 13:23:42 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/01 10:04:40 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	swap(void **a, void **b)
{
	void *c;

	c = *a;
	*a = *b;
	*b = c;
}

/*
** Hoare partition function
*/

static int	partition(void **arr, int start, int end,
		int (*cmp)(void *, void *))
{
	int		i;
	int		j;
	void	*x;

	i = start;
	j = end;
	x = arr[start];
	while (1)
	{
		while (cmp(arr[i], x) == -1)
			++i;
		while (cmp(arr[j], x) == 1)
			--j;
		if (i < j)
			swap(&arr[i++], &arr[j--]);
		else
			return (j);
	}
}

/*
** Function sorts array of pointers from less to high
** using quicksort algorithm
**
** @param	arr		array to sort
** @param	se		x has to indicate start of the array (0),
** 					y has to indicate end of the array (arrsize)
** @param	cmp		function to compare two elements. Has to return
** 					1 if first element is bigger than second,
** 					-1 if first element is less than second,
** 					0 when elements are equal
*/

void		ft_qsarr(void **arr, int start, int end, int (*cmp)(void *, void *))
{
	int idx;

	if (start < end)
	{
		idx = partition(arr, start, end, cmp);
		ft_qsarr(arr, start, idx, cmp);
		ft_qsarr(arr, idx + 1, end, cmp);
	}
}
