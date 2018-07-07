/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcontains.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 10:48:59 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/05 11:14:47 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_lstcontains(t_list *lst, t_list *sn, int (*check)(t_list *cn, t_list *sn))
{
	while (lst)
	{
		if (check(lst, sn))
			return (1);
		lst = lst->next;
	}
	return (0);
}
