/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_room_bad_x.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/23 11:41:11 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_err	*raise_room_bad_x(char *num1)
{
	t_err *err;

	err = new_err(ERR_ROOM_BAD_X, num1, ft_strlen(num1) + 1);
	return (err);
}

char	*hlr_room_bad_x(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	err_msg = ft_format("%s%sError%s:%s%d%s: bad %sx%s coordinate "
			"'%s%s%s'\n", &ln, UNDERLINE, CYAN, RESET, BOLD, line,
			RESET, GREEN, RESET, RED, (char *)*extra, RESET);
	ft_strdel((char**)extra);
	return (err_msg);
}
