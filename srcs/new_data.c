/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:40:57 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/04 16:02:35 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lmdata	*new_data(int adj_ds)
{
	int			i;
	t_lmdata	*data;

	i = 0;
	data = (t_lmdata*)ft_memalloc(sizeof(t_lmdata));
	data->adj = (t_list **)ft_memalloc(sizeof(t_list *) * adj_ds);
	data->adj_as = adj_ds;
	return (data);
}
