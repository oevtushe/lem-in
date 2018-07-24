/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_link_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:46:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/23 16:47:21 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lm_errs.h"

void	li_link_double(t_err *err, char **input, int size)
{
	int		i;
	char	*cl;
	t_pair	*inner;

	cl = ft_strjoin((char *)((t_pair*)err->extra)->fst, "-");
	ft_strconnect(&cl, (char *)((t_pair*)err->extra)->scd, 1);
	i = find_in_pinput(input, size, cl);
	// connect string in second order
	if (i == -1)
	{
		ft_strdel(&cl);
		cl = ft_strjoin((char *)((t_pair*)err->extra)->scd, "-");
		ft_strconnect(&cl, (char *)((t_pair*)err->extra)->fst, 1);
		i = find_in_pinput(input, size, cl);
	}
	if (i != -1)
	{
		++i;
		inner = ft_memalloc(sizeof(t_pair));
		inner->fst = ((t_pair*)err->extra)->fst;
		inner->scd = ((t_pair*)err->extra)->scd;
		((t_pair*)err->extra)->fst = ft_memdup(&i, sizeof(int));
		((t_pair*)err->extra)->scd = inner;
	}
}

t_err	*raise_link_double(char *fst, char *scd)
{
	t_err	*err;
	t_pair	*pair;

	pair = ft_newpair(fst, ft_strlen(fst) + 1, scd, ft_strlen(scd) + 1);
	err = new_err(ERR_LINK_DOUBLE, pair, sizeof(t_pair));
	ft_memdel((void**)&pair);
	return (err);
}

char	*hlr_link_double(void **extra, int line)
{
	size_t	ln;
	char	*err_msg;
	t_pair	*p1;
	t_pair	*p2;

	p1 = (t_pair *)*extra;
	p2 = (t_pair*)p1->scd;
	err_msg = ft_format("%s%sError%s:%s%d%s: room '%s%s%s' and"
			" '%s%s%s' are already linked in line %s%d%s\n", &ln,
			UNDERLINE, CYAN, RESET, BOLD, line, RESET, RED,
			(char *)p2->fst, RESET, RED, (char *)p2->scd,
			RESET, BOLD, *(int*)p1->fst, RESET);
	ft_strdel((char **)&p2->fst);
	ft_strdel((char **)&p2->scd);
	ft_memdel((void **)&p1->scd);
	ft_memdel((void **)&p1->fst);
	ft_memdel((void **)extra);
	return (err_msg);
}
