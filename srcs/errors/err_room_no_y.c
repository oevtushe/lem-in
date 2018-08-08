/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_room_no_y.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 18:41:24 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

t_err	*raise_room_no_y(char *line)
{
	t_err	*err;

	err = new_err(ERR_ROOM_NO_Y, line, ft_strlen(line) + 1);
	return (err);
}

char	*hlr_room_no_y(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	err_msg = ft_format("%s%sError%s:%s%d%s: %sy%s coordinate not "
			"specified '%s%s%s'\n", &ln, UNDERLINE, CYAN, RESET, BOLD,
			line, RESET, GREEN, RESET, RED, (char *)*extra, RESET);
	return (err_msg);
}
