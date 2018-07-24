/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_room_bad_y.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/23 16:47:38 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

t_err	*raise_room_bad_y(char *num2)
{
	t_err *err;

	err = new_err(ERR_ROOM_BAD_Y, num2, ft_strlen(num2) + 1);
	return (err);
}

char	*hlr_room_bad_y(void **extra, int line)
{
	size_t	ln;
	char *err_msg;

	err_msg = ft_format("%s%sError%s:%s%d%s: bad %sy%s coordinate '%s%s%s'\n",
			&ln, UNDERLINE, CYAN, RESET, BOLD, line, RESET, GREEN, RESET,
			RED, (char *)*extra, RESET);
	ft_strdel((char **)extra);
	return (err_msg);
}
