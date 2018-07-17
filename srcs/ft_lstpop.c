/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 11:06:24 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/17 11:37:53 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	*ft_lstpop(t_list **lst)
{
	t_list	*last;
	t_list	*runner;
	void	*data;

	runner = *lst;
	data = NULL;
	if (lst && *lst)
	{
		if ((*lst)->next)
		{
			while (runner->next->next)
				runner = runner->next;
			last = runner->next;
			data = last->content;
			ft_memdel((void**)&last);
			runner->next = NULL;
		}
		else
		{
			last = *lst;
			data = last->content;
			ft_memdel((void**)&last);
			*lst = NULL;
		}
	}
	return (data);
}
