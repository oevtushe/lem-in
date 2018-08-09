/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_cmd_double_start.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/09 09:29:02 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

t_err	*raise_cmd_double_start(void)
{
	t_err *err;

	err = new_err(ERR_CMD_DOUBLE_START, NULL, 0);
	return (err);
}

char	*hlr_cmd_double_start(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	err_msg = ft_format("%s%sError%s:%s%d%s: %sstart%s is already defined"
			" in line %s%d%s\n", &ln, UNDERLINE, CYAN, RESET, BOLD,
			line, RESET, GREEN, RESET, BOLD, *(int*)*extra, RESET);
	ft_strdel((char **)extra);
	return (err_msg);
}
