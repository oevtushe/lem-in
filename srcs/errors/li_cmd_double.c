/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_cmd_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 19:05:01 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/02 12:07:37 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

static int	cmp_safe(void *elem, void *data)
{
	if (elem && data)
	{
		if (!ft_strcmp((char *)elem, (char *)data))
			return (1);
	}
	return (0);
}

void		li_cmd_double(t_err *err, char **input, int size)
{
	int		i;

	i = -1;
	if (err->err_code == ERR_CMD_DOUBLE_START)
		i = ft_arrgetidx((void **)input, size, "##start", cmp_safe);
	else if (err->err_code == ERR_CMD_DOUBLE_END)
		i = ft_arrgetidx((void **)input, size, "##end", cmp_safe);
	if (i != -1 && i != (size - 1))
	{
		++i;
		err->extra = ft_memdup(&i, sizeof(int));
	}
}
