/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_cmd_bad_using.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:27 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 18:39:44 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

t_err	*raise_cmd_bad_using(char *line)
{
	t_err *err;

	err = new_err(ERR_CMD_BAD_USING, line, ft_strlen(line) + 1);
	return (err);
}

char	*hlr_cmd_bad_using(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	err_msg = ft_format("%s%sError%s:%s%d%s: %sroom%s specification "
				"expected '%s%s%s'\n", &ln, UNDERLINE, CYAN, RESET,
				BOLD, line, RESET, GREEN, RESET, RED, (char *)*extra, RESET);
	return (err_msg);
}
