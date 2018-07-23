/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_cmd_double_end.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:27 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/20 18:46:27 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_err	*raise_cmd_double_end(void)
{
	t_err *err;

	err = new_err(ERR_CMD_DOUBLE_END, NULL, 0);
	return (err);
}

char	*hlr_cmd_double_end(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	err_msg = ft_format("%s%sError%s:%s%d%s: %send%s is already defined "
			"in line %s%d%s\n", &ln, UNDERLINE, CYAN, RESET, BOLD,
			line, RESET, GREEN, RESET, BOLD, *(int*)*extra, RESET);
	ft_memdel((void **)extra);
	return (err_msg);
}
