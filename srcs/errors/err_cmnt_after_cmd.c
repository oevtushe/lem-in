/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_cmnt_after_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 10:58:48 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 18:39:55 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_err	*raise_cmnt_after_cmd(char *line)
{
	t_err *err;

	err = new_err(ERR_CMNT_AFTER_CMD, line, ft_strlen(line) + 1);
	return (err);
}

char	*hlr_cmnt_after_cmd(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	err_msg = ft_format("%s%sError%s:%s%d%s: %scomments%s"
			" aren't allowed straight after %scmd%s definition"
			" '%s%s%s'\n", &ln, UNDERLINE, CYAN, RESET, BOLD,
			line, RESET, GREEN, RESET, GREEN, RESET, RED, *extra, RESET);
	return (err_msg);
}
