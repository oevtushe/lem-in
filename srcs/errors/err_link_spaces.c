/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_link_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 18:40:41 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

t_err	*raise_link_spaces(char *line, char *st1, char *st2)
{
	t_err *err;

	if (ft_strchr(st1, ' '))
		err = new_err(ERR_LINK_SPACES, st1, ft_strlen(st1) + 1);
	else if (ft_strchr(st2, ' '))
		err = new_err(ERR_LINK_SPACES, st2, ft_strlen(st2) + 1);
	else
		err = new_err(ERR_LINK_SPACES, line, ft_strlen(line) + 1);
	return (err);
}

char	*hlr_link_spaces(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	err_msg = ft_format("%s%sError%s:%s%d%s: spaces are not allowed "
			"'%s%s%s'\n", &ln, UNDERLINE, CYAN, RESET, BOLD, line,
				RESET, RED, *extra, RESET);
	ft_strdel((char **)extra);
	return (err_msg);
}
