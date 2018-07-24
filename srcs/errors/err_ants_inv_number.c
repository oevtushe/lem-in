/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_ants_inv_number.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:27 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/23 16:45:19 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

t_err	*raise_ants_inv_number(char *line)
{
	t_err *err;

	err = new_err(ERR_ANTS_INV_NUMBER, line, ft_strlen(line) + 1);
	return (err);
}

char *hlr_ants_inv_number(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	err_msg = ft_format("%s%sError%s:%s%d%s: Invalid number of ants "
			"'%s%s%s'\n", &ln, UNDERLINE, CYAN, RESET, BOLD, line,
			RESET, RED, (char*)*extra, RESET);
	ft_strdel((char **)extra);
	return (err_msg);
}
