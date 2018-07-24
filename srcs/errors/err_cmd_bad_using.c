/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_cmd_bad_using.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:27 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/23 16:46:13 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

t_err	*raise_cmd_bad_using(void)
{
	t_err *err;

	err = new_err(ERR_CMD_BAD_USING, NULL, 0);
	return (err);
}

char	*hlr_cmd_bad_using(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	extra = NULL;
	err_msg = ft_format("%s%sError%s:%s%d%s: room specification expected, "
			"no commands are allowed here\n", &ln, UNDERLINE, CYAN, RESET,
			BOLD, line, RESET);
	return (err_msg);
}