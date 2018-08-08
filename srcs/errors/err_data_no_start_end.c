/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_data_no_start_end.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 18:40:16 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

t_err	*raise_data_no_start_end(void)
{
	t_err *err;

	err = new_err(ERR_DATA_NO_START_END, NULL, 0);
	return (err);
}

char	*hlr_data_no_start_end(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	line = 0;
	extra = NULL;
	err_msg = ft_format("%s%sError%s: no %sstart%s & %send%s defined\n",
			&ln, UNDERLINE, CYAN, RESET, GREEN, RESET, GREEN, RESET);
	return (err_msg);
}
