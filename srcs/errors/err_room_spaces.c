/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_room_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 16:44:14 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 18:41:28 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

t_err	*raise_room_spaces(char *line)
{
	t_err *err;

	err = new_err(ERR_ROOM_SPACES, line, ft_strlen(line) + 1);
	return (err);
}

char	*hlr_room_spaces(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	err_msg = ft_format("%s%sError%s:%s%d%s: "
			"extra spaces were found in line '%s%s%s'\n",
				&ln, UNDERLINE, CYAN, RESET, BOLD, line,
					RESET, RED, (char *)*extra, RESET);
	return (err_msg);
}
