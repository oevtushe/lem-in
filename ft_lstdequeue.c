/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdequeue.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 19:54:44 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/07 19:58:42 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	*ft_lstdequeue(t_list **root)
{
	t_list	*fst;
	void	*content;

	fst = *root;
	*root = (*root)->next;
	content = fst-content;
	ft_memdel((void **)&fst);
	return (content);
}
