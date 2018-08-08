/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:27:51 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 18:59:54 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "lem_in.h"

static int	set_option(void *container, char option)
{
	t_po	*po;
	int		res;

	res = 1;
	po = (t_po *)container;
	if (option == 'e')
		po->e = 1;
	else if (option == 'p')
		po->p = 1;
	else if (option == 's')
	{
		po->s = 1;
		po->p = 1;
	}
	else if (option == 'q')
		po->q = 1;
	else
		res = 0;
	return (res);
}

static void	print_usage(void)
{
	ft_printf("Usage: ./lem-in -[epsq]\n"
			"-e -> extended error printing\n"
			"-p -> pretty output\n"
			"-s -> statistics (turns on -p too)\n"
			"-q -> quiet mode. No map printing\n");
}

int			main(int argc, char **argv)
{
	t_list		*paths;
	t_err		*err;
	t_lmdata	*data;
	t_po		po;

	err = NULL;
	ft_memset(&po, 0, sizeof(t_po));
	if (argc > 1 && !ft_argsparser(&argv[1], argc - 1, (void *)&po, set_option))
	{
		print_usage();
		return (42);
	}
	if ((data = read_data(&err)) && !err)
	{
		paths = get_paths(data);
		if (paths)
			mk_output(data, &po, &paths);
		else
			err = raise_data_no_path();
		ft_lstdel(&paths, del_rebased_paths);
	}
	if (err)
		error_handler(err, po.e);
	free_lmdata(&data);
	return (0);
}
