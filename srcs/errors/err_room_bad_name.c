/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_room_bad_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/23 16:47:34 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

t_err	*raise_room_bad_name(char *line)
{
	t_err *err;

	err = new_err(ERR_ROOM_BAD_NAME, line, ft_strlen(line) + 1);
	return (err);
}

char	*hlr_room_bad_name(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	err_msg = ft_format("%s%sError%s:%s%d%s: bad room name '%s%s%s'\n"
				"Room name can't contain a '%s%c%s' character\n",
				&ln, UNDERLINE, CYAN, RESET, BOLD, line, RESET,\
				RED, (char*)*extra, RESET,\
				RED, ((char*)*extra)[0], RESET);
	ft_strdel((char **)extra);
	return (err_msg);
}
