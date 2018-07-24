/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_cmd_double_start.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/23 16:47:09 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

void	li_cmd_double(t_err *err, char **input, int size)
{
	int		i;

	i = -1;
	if (err->err_code == ERR_CMD_DOUBLE_START)
		i = find_in_pinput(input, size, "##start");
	else if (err->err_code == ERR_CMD_DOUBLE_END)
		i = find_in_pinput(input, size, "##end");
	if (i != -1)
	{
		++i;
		err->extra = ft_memdup(&i, sizeof(int));
	}
}

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
