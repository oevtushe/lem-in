/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_ants_inv_num.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 10:50:05 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/09 09:26:56 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

t_err	*raise_ants_inv_num(char *line)
{
	t_err *err;

	err = new_err(ERR_ANTS_INV_NUM, line, ft_strlen(line) + 1);
	return (err);
}

char	*hlr_ants_inv_num(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	err_msg = ft_format("%s%sError%s:%s%d%s: "
			"number of ants must be a positive non-zero integer "
			"'%s%s%s'\n", &ln, UNDERLINE, CYAN, RESET, BOLD, line,
			RESET, RED, (char*)*extra, RESET);
	ft_strdel((char **)extra);
	return (err_msg);
}
