/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_link_not_existing_room.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/23 12:08:50 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_err	*raise_link_not_existing_room(char *line)
{
	t_err *err;

	err = new_err(ERR_LINK_NOT_EXISTING_ROOM, line, ft_strlen(line) + 1);
	return (err);
}

char	*hlr_link_not_existing_room(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	err_msg = ft_format("%s%sError%s:%s%d%s: using not existing "
			"room '%s%s%s'\n", &ln, UNDERLINE, CYAN, RESET, BOLD,
			line, RESET, RED, (char*)*extra, RESET);
	ft_strdel((char **)extra);
	return (err_msg);
}
