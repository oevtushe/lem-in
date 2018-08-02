/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argsparser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 15:07:28 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/01 16:55:39 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Function for program's options parsing.
** Options may be passed as '-a' '-r' etc..
** or combined '-ar' ...
** Notice:
** 		pass only array with options, array mustn't contain
** 		first program argument (program name)
**
** @param	argv		array of arguments (without program name)
** @param	size		size of the array of arguments (without program name)
** @param	container	conteiner which will hold passed arguments
** @param	set_option	function which checks current option
** 						and sets this option to the container, if option is
** 						valid function returns 1, 0 otherwise.
** @return	1			if all options were valid
** 			0			if 1 or more options were invalid
*/

int		ft_argsparser(char **argv, int size, void *container,
			int (*set_option)(void *container, char option))
{
	int		i;
	int		j;
	int		len;
	int		res;

	i = 0;
	len = 0;
	res = 0;
	while (i < size)
	{
		len = (int)ft_strlen(argv[i]);
		if (argv[i][0] == '-' && len > 1)
		{
			j = 0;
			while (++j < len)
				if (!set_option(container, argv[i][j]))
					break ;
		}
		else
			break ;
		++i;
	}
	if (i == size && j == len)
		res = 1;
	return (res);
}
