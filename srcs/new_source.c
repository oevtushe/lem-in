/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_source.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 12:19:02 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/12 12:21:27 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_source	*new_source(t_list *s, t_list *black_list)
{
	t_source *source;

	source = NULL;
	if (s)
	{
		source->nodes = s;
		source->black_list = black_list;
	}
	return (source);
}
