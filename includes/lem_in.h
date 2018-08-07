/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:31:45 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/07 18:24:54 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf.h"
# include "lm_errs.h"

# define BC_STOP 100

typedef struct	s_rdata
{
	int 	cmd_mode;
	int		data_type;
}				t_rdata;

typedef struct	s_po
{
	int e;
	int o;
	int p;
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

void		pdecode_paths(t_list *paths, int *aop);
char		*check_overlapping(t_lmdata *data, t_list *paths, t_list *path);
char		*backtracking(t_lmdata *data, t_pair *paths, t_pair *roots, int *bn);
t_err		*add_link(t_lmdata *data, char *fst, char *scd);
t_list		*clone_node(t_list *room);
int			get_node_idx(t_lmdata *data, char *name);
void		check_adj(t_lmdata *data);
void		realloc_input(char ***input, int *size);
void		realloc_adj(t_lmdata *data);
void		ft_realloc(void **mem, size_t old_size, size_t new_size);
t_lmdata	*new_data(int mds);
t_node		*new_node(char *line, int x, int y);
void		del_node(void *content, size_t content_size);
t_list		*new_room_node(char *name, int x, int y);
void		free_node(t_node **node);
void		print_path(t_lmdata *data);
void		save_path(t_lmdata *data, t_list **path);
void		bfs(t_lmdata *data, t_list *start, t_list *black_list, int (*check)(void *, void *));
void		wash_up_map(t_lmdata *data);
void		add_path_to_blacklist(t_list **black_list, t_list *path);
void		add_node_to_blacklist(t_list **black_list, char *o);
void		del_link(t_lmdata *data, char *n1, char *n2);
void		ft_qsarr(void **arr, int start, int end, int (*cmp)(void *, void *));
void		**ft_lsttoarr(t_list *lst);
t_list		*ft_arrtolst(void **arr, int size);
t_list		*ft_lstnew_cc(void *content, size_t content_size);
void		ft_freepa_sd(void ***arr, int size);
void		ft_freepa(void ***arr, int size, void (*del)(void *content));
int			ft_argsparser(char **argv, int size, void *container,
				int (*set_option)(void *container, char option));
void		del_empty_node(void *content, size_t content_size);

t_err		*parse_link(char *line, t_lmdata *data);
t_err		*parse_room(char *line, t_lmdata *data, int cmd_mode, t_pair *extra);
t_err		*parse_command(char *line, int *cmd_mode, t_pair *extra);

int			cmp_len(void *a, void *b);
int			cmp_lst_str(void *elem, void *data);
int			cmp_lst_str(void *elem, void *data);
int			cmp_str_str(void *cn, void *sn);

t_lmdata	*read_data(t_err **err);
t_err		*read_ants(int *ants);
void		print_paths(t_list *paths);
t_list		*copy_rebased_paths(t_list *path_lst);
t_list		*copy_simple_paths(t_list *paths_node);
void		del_simple_paths(void *content, size_t content_size);
t_node		*dup_node(t_node *room);
t_list		*map_path_list(t_list *elem);
void		del_int(void *content, size_t content_size);

void		free_lmdata(t_lmdata **data);
void		do_err(t_err **err, t_lmdata *data, int i);
void		do_cmd_inv(int cmd_mode, char **line, t_err **err);
void		li_handler(t_err *err, char **input, int size);
void		further_handlers(t_err **err, t_pair *extra);

/*
** For tests
*/

void		print_rooms(t_list *elem);

#endif
