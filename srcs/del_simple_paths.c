/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_simple_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 19:13:04 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/07 18:55:43 by oevtushe         ###   ########.fr       */
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

void		del_rebased_paths(void *content, size_t content_size)
{
	t_path *path;

	content_size = 0;
	path = (t_path *)content;
	ft_lstdel(&path->list, del_node);
	ft_memdel((void **)&path);
}
