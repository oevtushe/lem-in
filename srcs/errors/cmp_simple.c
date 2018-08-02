/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_simple.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 19:00:08 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/02 12:08:28 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

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
