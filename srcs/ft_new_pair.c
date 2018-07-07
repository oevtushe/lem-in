/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_pair.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 18:59:50 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/07 19:11:05 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_pair	*ft_new_pair(void *fst, void *scd)
{
	t_pair *pair;

	pair = (t_pair *)ft_memalloc(sizeof(t_pair));
	pair->fst = fst;
	pair->scd = scd;
	return (pair);
}
