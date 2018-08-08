/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_room_double_def.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 18:41:11 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

/*
** late init
*/

void	li_room_double_def(t_err *err, char **input, int size)
{
	int		i;
	t_pair	*pair;
	t_pair	*inner;

	i = ft_arrgetidx((void **)input, size, err->extra, cmp_simple);
	if (i != -1 && i != (size - 1))
	{
		++i;
		pair = (t_pair*)ft_memalloc(sizeof(t_pair));
		pair->fst = err->extra;
		inner = ft_newpair(&i, sizeof(int), input[i - 1],
				ft_strlen(input[i - 1]) + 1);
		pair->scd = inner;
		err->extra = pair;
	}
}

t_err	*raise_room_double_def(char *line)
{
	t_err *err;

	err = new_err(ERR_ROOM_DOUBLE_DEF, line, ft_strlen(line) + 1);
	return (err);
}

char	*hlr_room_double_def(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;
	t_pair	*p1;
	t_pair	*p2;

	p1 = (t_pair *)*extra;
	p2 = (t_pair *)p1->scd;
	err_msg = ft_format("%s%sError%s:%s%d%s: room with name '%s%s%s' "
			"has already been defined as '%s%s%s' in line: %s%d%s\n",
			&ln, UNDERLINE, CYAN, RESET, BOLD, line, RESET, RED,
			(char*)p1->fst, RESET, RED,
			(char*)p2->scd, RESET, BOLD,
			*(int*)p2->fst, RESET);
	return (err_msg);
}
