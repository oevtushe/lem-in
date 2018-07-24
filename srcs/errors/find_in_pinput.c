/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_pinput.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 12:06:39 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/23 17:41:39 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		find_in_pinput(char **input, int size, char *line)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(line);
	while (i < size)
	{
		if (input[i])
			if (!ft_strncmp(input[i], line, len))
				break ;
		++i;
	}
	if (i != size && i != (size - 1))
		return (i);
	return (-1);
}
