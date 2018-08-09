/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_room_bad_coord.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 18:40:50 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

t_err	*raise_room_bad_coord(char *num1, char *num2)
{
	t_err	*err;
	t_pair	*pair;

	pair = ft_newpair(num1, ft_strlen(num1) + 1, num2, ft_strlen(num2) + 1);
	err = new_err(ERR_ROOM_BAD_COORD, pair, sizeof(t_pair));
	ft_memdel((void**)&pair);
	return (err);
}

char	*hlr_room_bad_coord(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;
	t_pair	*p;

	p = (t_pair*)*extra;
	err_msg = ft_format("%s%sError%s:%s%d%s: bad coordinates '%s%s%s' "
			"and '%s%s%s'\n", &ln, UNDERLINE, CYAN, RESET, BOLD, line,
			RESET, RED, (char*)p->fst, RESET, RED,
			(char*)p->scd, RESET);
	ft_strdel((char **)&p->fst);
	ft_strdel((char **)&p->scd);
	ft_memdel(extra);
	return (err_msg);
}
