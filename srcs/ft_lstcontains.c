/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcontains.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 10:48:59 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/13 13:30:23 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_lstcontains(t_list *lst, void *data, int (*check)(t_list *elem, void *data))
{
	while (lst)
	{
		if (check(lst, data))
			return (1);
		lst = lst->next;
	}
	return (0);
}
