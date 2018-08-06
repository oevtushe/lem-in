/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_simple_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 19:13:04 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/06 19:20:39 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		del_simple_paths(void *content, size_t content_size)
{
	t_list *path;

	content_size = 0;
	path = (t_list *)content;
	ft_lstdel(&path, del_node);
}
