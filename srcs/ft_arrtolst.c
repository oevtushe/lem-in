/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrtolst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 15:26:38 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/03 15:50:31 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Function converts array of pointers to list
** Data from the array won't be copied, just captured by pointer
*/

t_list *ft_arrtolst(void **arr, int size)
{
	int		i;
	t_list	*begin;
	t_list	*last;

	i = 0;
	begin = NULL;
	last = NULL;
	if (size && arr)
	{
		last = ft_lstnew_cc(arr[i++], sizeof(t_list));
		begin = last;
		while (i < size)
		{
			last->next = ft_lstnew_cc(arr[i], sizeof(t_list));
			last = last->next;
			++i;
		}
	}
	return (begin);
}
