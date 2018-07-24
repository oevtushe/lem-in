/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_data_no_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 10:52:04 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/24 11:06:37 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

t_err	*raise_data_no_path(void)
{
	t_err	*err;

	err = new_err(ERR_DATA_NO_PATH, NULL, 0);
	return (err);
}

char	*hlr_data_no_path(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;

	extra = NULL;
	line = 0;
	err_msg = ft_format("%s%sError%s: no path between "
			"%sstart%s and %send%s\n", &ln, UNDERLINE, CYAN, RESET, 
			GREEN, RESET, GREEN, RESET);
	return (err_msg);
}
