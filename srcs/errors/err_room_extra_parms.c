/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_room_extra_parms.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/23 12:10:24 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_err	*raise_room_extra_parms(char **arr, int size, char *line)
{
	t_err	*err;
	t_pair	*pair;
	char	*imploded;

	imploded = ft_strimplode(&arr[3], size - 3, " ");
	pair = ft_newpair(line, ft_strlen(line) + 1, imploded, ft_strlen(imploded) + 1);
	err = new_err(ERR_ROOM_EXTRA_PARMS, pair, sizeof(t_pair));
	ft_strdel(&imploded);
	ft_memdel((void**)&pair);
	return (err);
}

char	*hlr_room_extra_parms(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;
	t_pair	*p;

	p = (t_pair *)*extra;
	err_msg = ft_format("%s%sError%s:%s%d%s: some extra parameters passed: "
			"'%s%s%s' in '%s%s%s' \n", &ln, UNDERLINE, CYAN, RESET, BOLD,
			line, RESET, RED, (char *)p->scd, RESET,\
			RED, (char *)p->fst, RESET);
	ft_strdel((char **)&p->fst);
	ft_strdel((char **)&p->scd);
	ft_memdel(extra);
	return (err_msg);
}
