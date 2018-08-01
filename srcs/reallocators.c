/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocators.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 16:17:56 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/31 16:24:01 by oevtushe         ###   ########.fr       */
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

void		realloc_input(char ***input, int *size)
{
	int new_len;

	new_len = *size + 10;
	ft_realloc((void **)input,
			*size * sizeof(void *), new_len * sizeof(void *));
	*size = new_len;
}
