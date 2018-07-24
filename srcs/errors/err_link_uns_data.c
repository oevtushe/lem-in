/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_link_uns_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/23 16:47:30 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

t_err	*raise_link_uns_data(char *line)
{
	t_err *err;

	err = new_err(ERR_LINK_UNS_DATA, line, ft_strlen(line) + 1);
	return (err);
}

char	*hlr_link_uns_data(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	err_msg = ft_format("%s%sError%s:%s%d%s: you must specify"
			" 2 rooms '%s%s%s'\n", &ln, UNDERLINE, CYAN, RESET,
			BOLD, line, RESET, RED, *extra, RESET);
	ft_strdel((char **)extra);
	return (err_msg);
}
