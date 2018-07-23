/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_data_no_start.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/20 18:55:04 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_err	*raise_data_no_start(void)
{
	t_err *err;

	err = new_err(ERR_DATA_NO_START, NULL, 0);
	return (err);
}

char *hlr_data_no_start(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	line = 0;
	extra = NULL;
	err_msg = ft_format("%s%sError%s: no start defined\n",
			&ln, UNDERLINE, CYAN, RESET);
	return (err_msg);
}
