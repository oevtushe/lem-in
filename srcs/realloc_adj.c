/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_adj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 09:11:12 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/04 09:21:36 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		realloc_adj(t_lmdata *data)
{
	size_t len;

	len = sizeof(void *) * data->adj_as;
	data->adj_as = len + 10;
	ft_realloc((void**)&data->adj, len, data->adj_as);
}
