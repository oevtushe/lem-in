/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_room_no_xy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 18:41:20 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

t_err	*raise_room_no_xy(char *line)
{
	t_err	*err;

	err = new_err(ERR_ROOM_NO_XY, line, ft_strlen(line) + 1);
	return (err);
}

char	*hlr_room_no_xy(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	err_msg = ft_format("%s%sError%s:%s%d%s: %sx%s and %sy%s coordinates "
			"not specified '%s%s%s'\n", &ln, UNDERLINE, CYAN, RESET, BOLD,
			line, RESET, GREEN, RESET, GREEN, RESET, RED,\
			(char *)*extra, RESET);
	ft_strdel((char **)extra);
	return (err_msg);
}
