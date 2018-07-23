/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_errs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 17:55:17 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/23 12:10:47 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LM_ERRS_H
# define LM_ERRS_H

# include "ft_printf.h"

typedef enum	e_err_code
{
	ERR_ROOM_BAD_NAME = 2,
	ERR_ROOM_DOUBLE_DEF = 3,
	ERR_ROOM_BAD_COORD = 4,
	ERR_ROOM_BAD_X = 5,
	ERR_ROOM_BAD_Y = 6,
	ERR_ROOM_NO_XY = 7,
	ERR_ROOM_NO_Y = 8,
	ERR_ROOM_EXTRA_PARMS = 9,
	ERR_LINK_EXTRA_LINK_CHRS = 10,
	ERR_LINK_SELF = 11,
	ERR_LINK_DOUBLE = 12,
	ERR_LINK_UNS_DATA = 13,
	ERR_LINK_SPACES = 14,
	ERR_LINK_NOT_EXISTING_ROOM = 18,
	ERR_CMD_DOUBLE_START = 19,
	ERR_CMD_DOUBLE_END = 20,
	ERR_CMD_BAD_USING = 21,
	ERR_DATA_EMPTY = 22,
	ERR_DATA_NO_START = 23,
	ERR_DATA_NO_END = 24,
	ERR_DATA_NO_START_END = 25,
	ERR_ANTS_INV_NUMBER = 26,
	ERR_PASS_FURTHER = 27,
	ERR_CMD_INV = 28,
	ERR_NONE = 29
}				t_err_code;

typedef struct	s_err
{
	t_err_code	err_code;
	int			line;
	void		*extra;
}				t_err;

typedef struct	s_err_dsp
{
	t_err_code	err_code;
	char		*(*err_handler)(void **, int);
}				t_err_dsp;

void		error_handler(t_err *err);

void		li_room_double_def(t_err *err, char **input, int size);
void		li_cmd_double(t_err *err, char **input, int size);
void		li_link_double(t_err *err, char **input, int size);

t_err		*raise_ants_inv_number(char *line);

t_err		*raise_cmd_bad_using(void);
t_err		*raise_cmd_double_end(void);
t_err		*raise_cmd_double_start(void);

t_err		*raise_data_empty(void);
t_err		*raise_data_no_end(void);
t_err		*raise_data_no_start(void);
t_err		*raise_data_no_start_end(void);

t_err		*raise_link_double(char *fst, char *scd);
t_err		*raise_link_extra_link_chrs(char *line);
t_err		*raise_link_not_existing_room(char *line);
t_err		*raise_link_self(char *line);
t_err		*raise_link_spaces(char *line, char *st1, char *st2);
t_err		*raise_link_uns_data(char *line);

t_err		*raise_room_bad_coord(char *num1, char *num2);
t_err		*raise_room_bad_name(char *line);
t_err		*raise_room_bad_x(char *num1);
t_err		*raise_room_bad_y(char *num2);
t_err		*raise_room_double_def(char *line);
t_err		*raise_room_extra_parms(char **arr, int size, char *line);
t_err		*raise_room_no_xy(char *line);
t_err		*raise_room_no_y(char *line);

char		*hlr_room_bad_name(void **extra, int line);
char		*hlr_room_double_def(void **extra, int line);
char		*hlr_room_bad_coord(void **extra, int line);
char		*hlr_room_bad_x(void **extra, int line);
char		*hlr_room_bad_y(void **extra, int line);
char		*hlr_room_extra_parms(void **extra, int line);
char		*hlr_room_no_xy(void **extra, int line);
char		*hlr_room_no_y(void **extra, int line);

char		*hlr_link_extra_link_chrs(void **extra, int line);
char		*hlr_link_spaces(void **extra, int line);
char		*hlr_link_uns_data(void **extra, int line);
char		*hlr_link_self(void **extra, int line);
char		*hlr_link_not_existing_room(void **extra, int line);
char		*hlr_link_double(void **extra, int line);

char		*hlr_cmd_double_start(void **extra, int line);
char		*hlr_cmd_double_end(void **extra, int line);
char		*hlr_cmd_bad_using(void **extra, int line);

char 		*hlr_data_empty(void **extra, int ln);
char 		*hlr_data_no_start(void **extra, int ln);
char 		*hlr_data_no_end(void **extra, int ln);
char 		*hlr_data_no_start_end(void **extra, int ln);

char		*hlr_ants_inv_number(void **extra, int line);

#endif
