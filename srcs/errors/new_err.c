/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 11:26:41 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/18 11:28:48 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_err *new_err(int err_code, void *extra, size_t extra_len)
{
	t_err *err;

	err = ft_memalloc(sizeof(t_err));
	err->err_code = err_code;
	if (extra)
		err->extra = ft_memdup(extra, extra_len);
	return (err);
}
