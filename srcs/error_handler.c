/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 12:26:52 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/19 19:28:38 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error_handler(t_err *err)
{
	if (err->err_code == ER_ROOM_BAD_NAME)
	{
		ft_printf("%s%sError%s:%s%d%s: bad room name '%s%s%s'\n", UNDERLINE, CYAN, RESET, BOLD, err->line, RESET, RED, (char*)err->extra, RESET);
		ft_printf("Room name can't contain a '%s%c%s' character\n", RED, ((char*)err->extra)[0], RESET);
	}
	else if (err->err_code == ER_ROOM_DOUBLE_DEF)
	{
		ft_printf("%s%sError%s:%s%d%s: room with name '%s%s%s' have already been defined as '%s%s%s' in line: %s%d%s\n", UNDERLINE, CYAN, RESET, BOLD, err->line, RESET, RED, (char*)((t_pair*)err->extra)->fst, RESET, RED, (char*)((t_pair*)((t_pair*)err->extra)->scd)->scd, RESET, BOLD, *(int*)((t_pair*)((t_pair*)err->extra)->scd)->fst, RESET);
	}
	else if (err->err_code == ER_ROOM_BAD_COORD)
	{
		ft_printf("%s%sError%s:%s%d%s: bad coordinates '%s%s%s' and '%s%s%s'\n", UNDERLINE, CYAN, RESET, BOLD, err->line, RESET, RED, (char*)((t_pair*)err->extra)->fst, RESET, RED, (char*)((t_pair*)err->extra)->scd, RESET);
	}
	else if (err->err_code == ER_ROOM_BAD_X)
	{
		ft_printf("%s%sError%s:%s%d%s: bad %sx%s coordinate '%s%s%s'\n", UNDERLINE, CYAN, RESET, BOLD, err->line, RESET, GREEN, RESET, RED, (char *)err->extra, RESET);
	}
	else if (err->err_code == ER_ROOM_BAD_Y)
		ft_printf("%s%sError%s:%s%d%s: bad %sy%s coordinate '%s%s%s'\n", UNDERLINE, CYAN, RESET, BOLD, err->line, RESET, GREEN, RESET, RED, (char *)err->extra, RESET);
	else if (err->err_code == ER_ROOM_EXTRA_PARMS)
		ft_printf("%s%sError%s:%s%d%s: some extra parameters passed: '%s%s%s' in '%s%s%s' \n", UNDERLINE, CYAN, RESET, BOLD, err->line, RESET, RED, (char *)((t_pair *)err->extra)->scd, RESET, RED, (char *)((t_pair *)err->extra)->fst, RESET);
	else if (err->err_code == ER_ROOM_NO_XY)
	{
		ft_printf("%s%sError%s:%s%d%s: %sx%s and %sy%s coordinates not specified '%s%s%s'\n", UNDERLINE, CYAN, RESET, BOLD, err->line, RESET, GREEN, RESET, GREEN, RESET, RED, (char *)err->extra, RESET);
	}
	else if (err->err_code == ER_ROOM_NO_Y)
		ft_printf("%s%sError%s:%s%d%s: %sy%s coordinate not specified '%s%s%s'\n", UNDERLINE, CYAN, RESET, BOLD, err->line, RESET, GREEN, RESET, RED, (char *)err->extra, RESET);
	else if (err->err_code == ER_LINK_EXTRA_LINK_CHRS)
	{
		ft_printf("%s%sError%s:%s%d%s: too much link characters '%s-%s' in line '%s%s%s'\n", UNDERLINE, CYAN, RESET, BOLD, err->line, RESET, BOLD, RESET, RED, (char*)err->extra, RESET);
	}
	else if (err->err_code == ER_LINK_SPACES)
	{
		ft_printf("%s%sError%s:%s%d%s: spaces are not allowed '%s%s%s'\n", UNDERLINE, CYAN, RESET, BOLD, err->line, RESET,  RED, (char*)err->extra, RESET);
	}
	else if (err->err_code == ER_LINK_UNS_DATA)
	{
		ft_printf("%s%sError%s:%s%d%s: you must specify 2 rooms '%s%s%s'\n", UNDERLINE, CYAN, RESET, BOLD, err->line, RESET, RED, (char*)err->extra, RESET);
	}
	else if (err->err_code == ER_CMD_DOUBLE_START)
	{
		ft_printf("%s%sError%s:%s%d%s: %sstart%s is already defined in line %s%d%s\n", UNDERLINE, CYAN, RESET, BOLD, err->line, RESET, GREEN, RESET, BOLD, *(int*)err->extra, RESET);
	}
	else if (err->err_code == ER_CMD_DOUBLE_END)
		ft_printf("%s%sError%s:%s%d%s: %send%s is already defined in line %s%d%s\n", UNDERLINE, CYAN, RESET, BOLD, err->line, RESET, GREEN, RESET, BOLD, *(int*)err->extra, RESET);
	else if (err->err_code == ER_CMD_BAD_USING)
	{
		ft_printf("%s%sError%s:%s%d%s: room specification expected, no commands are allowed here\n", UNDERLINE, CYAN, RESET, BOLD, err->line, RESET);
	}
	else if (err->err_code == ER_ANTS_INV_NUMBER)
	{
		ft_printf("%s%sError%s:%s%d%s: Invalid number of ants '%s%s%s'\n", UNDERLINE, CYAN, RESET, BOLD, err->line, RESET, RED, (char*)err->extra, RESET);
	}
	else if (err->err_code == ER_DATA_EMPTY)
	{
		ft_printf("%s%sError%s: No input data\n", UNDERLINE, CYAN, RESET);
	}
	else if (err->err_code == ER_DATA_NO_START)
		ft_printf("%s%sError%s: no start defined\n", UNDERLINE, CYAN, RESET);
	else if (err->err_code == ER_DATA_NO_END)
		ft_printf("%s%sError%s: no end defined\n", UNDERLINE, CYAN, RESET);
	else if (err->err_code == ER_DATA_NO_START_END)
		ft_printf("%s%sError%s: no start & end defined\n", UNDERLINE, CYAN, RESET);
	else if (err->err_code == ER_LINK_DOUBLE)
		ft_printf("%s%sError%s:%s%d%s: room '%s%s%s' and '%s%s%s' are already linked in line %s%d%s\n", UNDERLINE, CYAN, RESET, BOLD, err->line, RESET, RED, (char *)((t_pair*)((t_pair*)err->extra)->scd)->fst, RESET, RED, (char *)((t_pair*)((t_pair*)err->extra)->scd)->scd, RESET, BOLD, *(int*)((t_pair*)err->extra)->fst, RESET);
	else if (err->err_code == ER_LINK_SELF)
		ft_printf("%s%sError%s:%s%d%s: selflink, room '%s%s%s'\n", UNDERLINE, CYAN, RESET, BOLD, err->line, RESET, RED, (char*)err->extra, RESET);
	else if (err->err_code == ER_LINK_NOT_EXISTING_ROOM)
		ft_printf("%s%sError%s:%s%d%s: using not existing room '%s%s%s'\n", UNDERLINE, CYAN, RESET, BOLD, err->line, RESET, RED, (char*)err->extra, RESET);
}
