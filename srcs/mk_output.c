/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mk_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 10:48:15 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 10:50:19 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>
#include <time.h>

static void	print_input(char **input, int size, t_po *po)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if (po->p && input[i])
			ft_printf("\033[38;5;35m%s\033[m\n", input[i]);
		else if (input[i])
			ft_printf("%s\n", input[i]);
		++i;
	}
	ft_putchar('\n');
}

static int	make_them_run(t_lmdata *data, t_list *paths, t_po *po, int *aop)
{
	int		al;
	int		moves;

	al = 0;
	moves = 0;
	while (move_ants(data, paths, &al, aop))
	{
		print_ants(paths, data->extra, po);
		++moves;
	}
	return (moves);
}

void		mk_output(t_lmdata *data, t_po *po, t_list **paths)
{
	int		*aop;
	int		moves;
	time_t	tm;

	srand((unsigned int)time(&tm));
	rebase_paths(*paths);
	if (!po->q)
		print_input(data->input, data->inp_size, po);
	aop = ft_memalloc(ft_lstlen(*paths) * sizeof(int));
	moves = make_them_run(data, *paths, po, aop);
	if (po->s)
	{
		ft_putchar('\n');
		pdecode_paths(*paths, aop);
		ft_printf("\n%sMoves%s: %d\n", ORANGE, RESET, moves);
	}
	ft_memdel((void **)&aop);
}
