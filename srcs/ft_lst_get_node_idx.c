/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_get_node_idx.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 18:18:56 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/16 18:18:57 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Function returns index of searched element in the list.
** If element wasn't found returns -1
*/

int		ft_lst_get_node_idx(t_list *lst, void *data, int (*check)(t_list *elem, void *data))
{
	int i;

	i = 0;
	while (lst)
	{
		if (check(lst, data))
			return (i);
		lst = lst->next;
		++i;
	}
	return (-1);
}
