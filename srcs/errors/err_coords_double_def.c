/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_coords_double_def.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 18:52:11 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/02 12:33:07 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

int		check_coords(void *elem, void *data)
{
	char	*e;
	char	*d;

	e = (char *)elem;
	d = (char *)data;
	if (elem && data)
	{
		if (e[0] != '#' && ft_strstr(e, d))
			return (1);
	}
	return (0);
}

void	li_coords_double_def(t_err *err, char **input, int size)
{
	int		i;
	t_pair	*pair;
	t_pair	*inner;

	i = ft_arrgetidx((void **)input, size, err->extra, check_coords);
	if (i != -1 && i != (size - 1))
	{
		++i;
		pair = (t_pair*)ft_memalloc(sizeof(t_pair));
		pair->fst = err->extra;
		inner = ft_newpair(&i, sizeof(int), input[i - 1], ft_strlen(input[i - 1]) + 1);
		pair->scd = inner;
		err->extra = pair;
	}
}

t_err	*raise_coords_double_def(char *x, char *y)
{
	t_err	*err;
	char	*comb;

	comb = ft_strjoin(x, " ");
	ft_strconnect(&comb, y, 1);
	err = new_err(ERR_COORDS_DOUBLE_DEF, comb, ft_strlen(comb) + 1);
	ft_strdel(&comb);
	return (err);
}

char	*hlr_coords_double_def(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;
	t_pair	*p1;
	t_pair	*p2;

	p1 = (t_pair *)*extra;
	p2 = (t_pair *)p1->scd;
	err_msg = ft_format("%s%sError%s:%s%d%s: such coordinates: '%s%s%s' "
			"has already been set: '%s%s%s' in line: %s%d%s\n",
			&ln, UNDERLINE, CYAN, RESET, BOLD, line, RESET, RED,
			(char*)p1->fst, RESET, RED,
			(char*)p2->scd, RESET, BOLD,
			*(int*)p2->fst, RESET);
	ft_memdel((void**)&p2->fst);
	ft_strdel((char**)&p2->scd);
	ft_memdel((void**)&p1->scd);
	ft_strdel((char**)&p1->fst);
	ft_memdel(extra);
	return (err_msg);
}
