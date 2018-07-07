/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:48:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/04 15:52:29 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Function reallocates memory
**
** Sizes should be given in bytes
** If current size is equall or bigger than new one, nothing will be done
*/

void	ft_realloc(void **mem, size_t old_size, size_t new_size)
{
	size_t	i;
	void	*new_mem;

	i = 0;
	if (old_size < new_size)
	{
		new_mem = ft_memalloc(new_size);
		ft_memcpy(new_mem, *mem, old_size);
		ft_memdel(mem);
		*mem = new_mem;
	}
}
