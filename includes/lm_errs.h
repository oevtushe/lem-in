/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_errs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 17:55:17 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/24 11:01:11 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LM_ERRS_H
# define LM_ERRS_H

# include "libft.h"
# include "ft_printf.h"

# define	DSP_SIZE 25

typedef enum	e_err_code
{
	ERR_ROOM_BAD_NAME,
	ERR_ROOM_DOUBLE_DEF,
	ERR_ROOM_BAD_COORD,
	ERR_ROOM_BAD_X,
	ERR_ROOM_BAD_Y,
	ERR_ROOM_NO_XY,
	ERR_ROOM_NO_Y,
	ERR_ROOM_EXTRA_PARMS,
	ERR_ROOM_SPACES,
	ERR_LINK_EXTRA_LINK_CHRS,
	ERR_LINK_SELF,
	ERR_LINK_DOUBLE,
	ERR_LINK_UNS_DATA,
	ERR_LINK_SPACES,
	ERR_LINK_NOT_EXISTING_ROOM,
	ERR_CMD_DOUBLE_START,
	ERR_CMD_DOUBLE_END,
	ERR_CMD_BAD_USING,
	ERR_DATA_EMPTY,
	ERR_DATA_NO_START,
	ERR_DATA_NO_END,
	ERR_DATA_NO_START_END,
	ERR_DATA_NO_PATH,
	ERR_ANTS_INV_NUMBER,
	ERR_PASS_FURTHER,
	ERR_CMD_INV,
	ERR_NONE
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

void		error_handler(t_err *err, int errors);
int			find_in_pinput(char **input, int size, char *line);
t_err 		*new_err(int err_code, void *extra, size_t extra_len);

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
t_err		*raise_data_no_path(void);

t_err		*raise_link_double(char *fst, char *scd);
t_err		*raise_link_extra_link_chrs(char *line);
t_err		*raise_link_not_existing_room(char *line);
t_err		*raise_link_self(char *line);
t_err		*raise_link_spaces(char *line, char *st1, char *st2);
t_err		*raise_link_uns_data(char *line);

t_err		*raise_room_spaces(char *line);
t_err		*raise_room_bad_coord(char *num1, char *num2);
t_err		*raise_room_bad_name(char *line);
t_err		*raise_room_bad_x(char *num1);
t_err		*raise_room_bad_y(char *num2);
t_err		*raise_room_double_def(char *line);
t_err		*raise_room_extra_parms(char **arr, int size, char *line);
t_err		*raise_room_no_xy(char *line);
t_err		*raise_room_no_y(char *line);

char		*hlr_room_spaces(void **extra, int line);
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
char		*hlr_data_no_path(void **extra, int line);

char		*hlr_ants_inv_number(void **extra, int line);

#endif
