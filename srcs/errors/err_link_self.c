/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_link_self.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 18:40:38 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

t_err	*raise_link_self(char *line)
{
	t_err *err;

	err = new_err(ERR_LINK_SELF, line, ft_strlen(line) + 1);
	return (err);
}

char	*hlr_link_self(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	err_msg = ft_format("%s%sError%s:%s%d%s: selflink, "
			"room '%s%s%s'\n", &ln, UNDERLINE, CYAN, RESET,
			BOLD, line, RESET, RED, (char*)*extra, RESET);
	ft_strdel((char **)extra);
	return (err_msg);
}
