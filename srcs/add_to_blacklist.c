/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_blacklist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 20:57:12 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/12 15:12:58 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_to_blacklist(t_list **black_list, int elem)
{
	t_list *node;

	node = ft_lstnew(&elem, sizeof(int));
	ft_lstappend(black_list, node);
}
