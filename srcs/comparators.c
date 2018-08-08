/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparators.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 16:45:39 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 16:25:27 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		cmp_str_str(void *cn, void *sn)
{
	if (ft_strequ((char *)cn, sn))
		return (1);
	return (0);
}

int		cmp_lst_str(void *elem, void *data)
{
	if (ft_strequ(((t_node *)elem)->name, (char *)data))
		return (1);
	return (0);
}

int		cmp_simple(void *elem, void *data)
{
	size_t	len;

	if (elem && data)
	{
		len = ft_strlen((char *)data);
		if (!ft_strncmp((char *)elem, (char *)data, len))
			return (1);
	}
	return (0);
}

int		cmp_len(void *a, void *b)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_lstlen((t_list *)a);
	len2 = ft_lstlen((t_list *)b);
	if (len1 > len2)
		return (1);
	else if (len1 < len2)
		return (-1);
	return (0);
}

int		cmp_str_node(void *elem, void *data)
{
	if (ft_strequ((char *)data, ((t_node *)elem)->name))
		return (1);
	return (0);
}
