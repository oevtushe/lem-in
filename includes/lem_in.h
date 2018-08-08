/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:31:45 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/08 18:28:30 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf.h"
# include "lm_errs.h"

# define BC_STOP 100

typedef struct	s_rdata
{
	int			cmd_mode;
	int			data_type;
}				t_rdata;

typedef struct	s_po
{
	int e;
	int p;
	int	q;
	int	s;
}				t_po;

typedef struct	s_lmdata
{
	int		ants;
	int		adj_as;
	int		adj_cs;
	t_pair	*extra;
	t_list	**adj;
	char	**input;
	int		inp_size;
}				t_lmdata;

typedef	struct	s_path
{
	int		color;
	t_list	*list;
}				t_path;

typedef struct	s_point
{
	int x;
	int y;
}				t_point;

typedef	struct	s_node
{
	int		x;
	int		y;
	char	*name;
	int		p;
	int		d;
	int		visited;
	int		ant;
	int		fresh;
}				t_node;

typedef struct	s_source
{
	t_list *black_list;
	t_list *nodes;
}				t_source;

void			pdecode_paths(t_list *paths, int *aop);
t_err			*add_link(t_lmdata *data, char *fst, char *scd);
t_list			*clone_node(t_list *room);
int				get_node_idx(t_lmdata *data, char *name);
void			check_adj(t_lmdata *data);
void			realloc_input(char ***input, int *size);
void			realloc_adj(t_lmdata *data);
t_lmdata		*new_data(int mds);
t_node			*new_node(char *line, int x, int y);
void			del_node(void *content, size_t content_size);
t_list			*new_room_node(char *name, int x, int y);
void			free_node(t_node **node);
void			print_path(t_lmdata *data);
void			save_path(t_lmdata *data, t_list **path);
void			bfs(t_lmdata *data, t_list *start,
					t_list *black_list, int (*check)(void *, void *));
void			wash_up_map(t_lmdata *data);
void			add_path_to_blacklist(t_list **black_list, t_list *path);
void			del_link(t_lmdata *data, char *n1, char *n2);
void			del_empty_node(void *content, size_t content_size);

t_err			*parse_link(char *line, t_lmdata *data);
t_err			*parse_room(char *line, t_lmdata *data,
					int cmd_mode, t_pair *extra);
t_err			*parse_command(char *line, int *cmd_mode, t_pair *extra);

int				cmp_len(void *a, void *b);
int				cmp_lst_str(void *elem, void *data);
int				cmp_lst_str(void *elem, void *data);
int				cmp_str_str(void *cn, void *sn);
int				cmp_str_node(void *elem, void *data);

t_lmdata		*read_data(t_err **err);
t_err			*read_ants(int *ants);
t_list			*copy_rebased_paths(t_list *path_lst);
t_list			*map_simple_paths(t_list *paths_node);
void			del_simple_paths(void *content, size_t content_size);
t_node			*dup_node(t_node *room);
t_list			*map_path_list(t_list *elem);
void			del_int(void *content, size_t content_size);

void			free_lmdata(t_lmdata **data);
void			do_err(t_err **err, t_lmdata *data, int i);
void			do_cmd_inv(int cmd_mode, char **line, t_err **err);
void			li_handler(t_err *err, char **input, int size);
void			further_handlers(t_err **err, t_pair *extra);
void			del_rebased_paths(void *content, size_t content_size);
t_list			*get_paths(t_lmdata *data);
void			print_ants(t_list *paths, t_pair *extra, t_po *po);
int				move_ants(t_lmdata *data, t_list *paths, int *al, int *aop);
void			rebase_paths(t_list *paths);
int				gen_color(t_list *colors);
t_err			*read_ants(int *ants);
void			mk_output(t_lmdata *data, t_po *po, t_list **paths);
void			check_path(t_pair *f, t_pair *extra, t_po *po, t_point *p);
void			print_ant(t_list *lst, t_pair *extra, t_po *po, t_path *path);
t_err			*gen_bad_coord_err(char *num1, char *num2);

#endif
