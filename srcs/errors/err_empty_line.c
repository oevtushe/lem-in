/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_empty_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 12:37:21 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 18:40:17 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

t_err	*raise_empty_line(void)
{
	t_err *err;

	err = new_err(ERR_EMPTY_LINE, NULL, 0);
	return (err);
}

char	*hlr_empty_line(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	extra = NULL;
	err_msg = ft_format("%s%sError%s:%s%d%s: empty lines not allowed\n",
			&ln, UNDERLINE, CYAN, RESET, BOLD, line, RESET);
	return (err_msg);
}
