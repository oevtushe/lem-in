/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 16:10:48 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/06 14:51:02 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	parse(t_lmdata **data, char **line, t_rdata *rdata)
{
	char **arr;

	arr = ft_strsplit(*line, ' ');
	if (rdata->data_type == 0 && (*line)[0] == '#' && (*line)[1] == '#')
		rdata->err = parse_command(*line, &rdata->cmd_mode, (*data)->extra);
	else if ((*line)[0] == '#')
	{
		if (rdata->cmd_mode)
			rdata->err = raise_cmnt_after_cmd(*line);
		return ;
	}
	else if (rdata->data_type == 0 && arr[0] && !ft_strchr(arr[0], '-') &&
			!(rdata->err = parse_room(*line, *data,
					rdata->cmd_mode, (*data)->extra)))
		rdata->cmd_mode = 0;
	else if (!rdata->err && (*data)->extra->fst && (*data)->extra->scd)
	{
		rdata->data_type = 1;
		rdata->err = parse_link(*line, *data);
	}
	else if (!rdata->err && rdata->cmd_mode)
		rdata->err = raise_cmd_bad_using(*line);
	else if (!rdata->err)
		rdata->err = new_err(ERR_PASS_FURTHER, NULL, 0);
}

static void		li_handler(t_err *err, char **input, int i)
{
	if (err->err_code == ERR_ROOM_DOUBLE_DEF)
		li_room_double_def(err, input, i);
	else if ((err->err_code == ERR_CMD_DOUBLE_START
				|| err->err_code == ERR_CMD_DOUBLE_END))
		li_cmd_double(err, input, i);
	else if (err->err_code == ERR_LINK_DOUBLE)
		li_link_double(err, input, i);
	else if (err->err_code == ERR_COORDS_DOUBLE_DEF)
		li_coords_double_def(err, input, i);
}

static void	further_handlers(t_err **err, t_pair *extra)
{
	if (!extra->fst && !extra->scd)
		*err = raise_data_no_start_end();
	else if  (!extra->fst)
		*err = raise_data_no_start();
	else if (!extra->scd)
		*err = raise_data_no_end();
}

static void	free_adj(void *content)
{
	t_node *node;

	node = (t_node *)(((t_list *)content)->content);
	ft_strdel(&node->name);
}

static void	do_err(t_err **err, t_lmdata *data, int i, int oerrs)
{
	if (*err)
	{
		(*err)->line = i;
		li_handler(*err, data->input, i);
	}
	if (!*err && (!data->extra->fst || !data->extra->scd))
		*err = new_err(ERR_PASS_FURTHER, NULL, 0);
	if (*err && (*err)->err_code == ERR_PASS_FURTHER)
		further_handlers(err, data->extra);
	error_handler(*err, oerrs);
}

static void	free_lmdata(t_lmdata **data)
{
	ft_freepa_sd((void ***)&(*data)->input, (*data)->inp_size);
	ft_freepa((void ***)&(*data)->adj, (*data)->adj_cs, free_adj);
	ft_memdel((void **)&(*data)->extra);
	ft_memdel((void **)data);
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

void		do_cmd_inv(int cmd_mode, char **line, t_err **err)
{
	if (cmd_mode)
		*err = raise_cmd_bad_using(*line);
	else
	{
		ft_memdel((void **)err);
		ft_strdel(line);
	}
}

t_lmdata	*read_data(int errors)
{
	int			i;
	char 		*line;
	t_rdata		rdata;
	t_lmdata	*data;

	i = 0;
	init_data(&data, &line, &rdata);
	rdata.err = read_ants(&data->ants);
	data->input[i++] = ft_itoa(data->ants);
	while (!rdata.err && get_next_line(0, &line))
	{
		if (!ft_strlen(line))
			rdata.err = raise_empty_line();
		else
			parse(&data, &line, &rdata);
		if (rdata.err && rdata.err->err_code == ERR_CMD_INV)
			do_cmd_inv(rdata.cmd_mode, &line, &rdata.err);
		if (i >= data->inp_size)
			realloc_input(&data->input, &data->inp_size);
		data->input[i++] = line;
	}
	data->inp_size = i;
	if (rdata.err || !data->extra->fst || !data->extra->scd)
	{
		do_err(&rdata.err, data, i, errors);
		free_lmdata(&data);
	}
	ft_realloc((void **)&data->input, i * sizeof(void *), i * sizeof(void *));
	return (data);
}
