/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newpair.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 11:54:49 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/18 14:21:45 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_pair	*ft_newpair(void *fst, size_t fst_size, void *scd, size_t scd_size)
{
	t_pair	*pair;
	void	*c1;
	void	*c2;

	pair = NULL;
	c1 = ft_memdup(fst, fst_size);
	if (c1)
	{
		c2 = ft_memdup(scd, scd_size);
		if (c2)
		{
			pair = (t_pair*)ft_memalloc(sizeof(t_pair));
			if (pair)
			{
				pair->fst = c1;
				pair->scd = c2;
			}
		}
	}
	return (pair);
}
