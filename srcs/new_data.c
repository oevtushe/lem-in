/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 15:40:57 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/17 12:21:28 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lmdata	*new_data(int adj_ds)
{
	t_lmdata	*data;

	data = (t_lmdata*)ft_memalloc(sizeof(t_lmdata));
	data->adj = (t_list **)ft_memalloc(sizeof(t_list *) * adj_ds);
	data->adj_as = adj_ds;
	data->extra = (t_pair *)ft_memalloc(sizeof(t_pair));
	return (data);
}
