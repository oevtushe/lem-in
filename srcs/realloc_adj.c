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
	size_t old_len;
	size_t new_len;

	old_len = data->adj_as * sizeof(void *);
	data->adj_as += 10;
	new_len = data->adj_as * sizeof(void *);
	ft_realloc((void**)&data->adj, old_len, new_len);
}
