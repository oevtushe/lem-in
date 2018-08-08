/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_link_not_existing_room.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 18:40:34 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

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
	return (err_msg);
}
