/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 16:10:48 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/07 18:20:03 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	parse(t_lmdata **data, char **line, t_rdata *rdata, t_err **err)
{
	char **arr;

	arr = ft_strsplit(*line, ' ');
	if (rdata->data_type == 0 && (*line)[0] == '#' && (*line)[1] == '#')
		*err = parse_command(*line, &rdata->cmd_mode, (*data)->extra);
	else if ((*line)[0] == '#')
	{
		if (rdata->cmd_mode)
			*err = raise_cmnt_after_cmd(*line);
		return ;
	}
	else if (rdata->data_type == 0 && arr[0] && !ft_strchr(arr[0], '-') &&
			!(*err = parse_room(*line, *data,
					rdata->cmd_mode, (*data)->extra)))
		rdata->cmd_mode = 0;
	else if (!*err && (*data)->extra->fst && (*data)->extra->scd)
	{
		rdata->data_type = 1;
		*err = parse_link(*line, *data);
	}
	else if (!*err && rdata->cmd_mode)
		*err = raise_cmd_bad_using(*line);
	else if (!*err)
		*err = new_err(ERR_PASS_FURTHER, NULL, 0);
}

static void	init_data(t_lmdata **data, char **line, t_rdata *rdata)
{
	*line = NULL;
	rdata->cmd_mode = 0;
	rdata->data_type = 0;
	*data = new_data(1);
	(*data)->inp_size = 1;
	ft_realloc((void **)&(*data)->input, 0, sizeof(void *) * (*data)->inp_size);
}

t_lmdata	*read_data(t_err **err)
{
	int			i;
	char 		*line;
	t_rdata		rdata;
	t_lmdata	*data;

	i = 0;
	init_data(&data, &line, &rdata);
	*err = read_ants(&data->ants);
	data->input[i++] = ft_itoa(data->ants);
	while (!*err && get_next_line(0, &line))
	{
		if (!ft_strlen(line))
			*err = raise_empty_line();
		else
			parse(&data, &line, &rdata, err);
		if (*err && (*err)->err_code == ERR_CMD_INV)
			do_cmd_inv(rdata.cmd_mode, &line, err);
		if (i >= data->inp_size)
			realloc_input(&data->input, &data->inp_size);
		data->input[i++] = line;
	}
	data->inp_size = i;
	if (*err || !data->extra->fst || !data->extra->scd)
	{
		do_err(err, data, i);
		free_lmdata(&data);
	}
	ft_realloc((void **)&data->input, i * sizeof(void *), i * sizeof(void *));
	return (data);
}
