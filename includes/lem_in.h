/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:31:45 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/23 12:06:59 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "lm_errs.h"

# define	DSP_SIZE 23

typedef struct	s_rdata
{
	int 	cmd_mode;
	int		data_type;
	t_err	*err;
}				t_rdata;

typedef struct	s_pair
{
	void *fst;
	void *scd;
}				t_pair;

typedef struct	s_lmdata
{
	int		ants;
	int		adj_as;
	int		adj_cs;
	t_pair	*extra;
	t_list	**adj;
}				t_lmdata;

typedef	struct	s_node
{
	int		x;
	int		y;
	char	*name;
	int		p;
	int		d;
	int		visited;
}				t_node;

typedef struct	s_source
{
	t_list *black_list;
	t_list *nodes;
}				t_source;

void		*ft_lstpop(t_list **lst);
void		pdecode_paths(t_lmdata *data, t_list *paths);
int			check_overlapping(t_list *paths, t_list *path);
//int			backtracking(t_lmdata *data, t_pair *paths, int root);
void		*ft_lstpeeklast(t_list *lst);
void		*ft_lstdequeue(t_list **root);
t_pair		*ft_new_pair(void *fst, void *scd);
int			ft_lst_get_node_idx(t_list *lst, void *data, int (*check)(t_list *elem, void *data));
int			ft_arrcontains(void **arr, int size, void *data, int (*check)(void *elem, void *data));
t_err		*add_link(t_lmdata *data, char *fst, char *scd);
t_list		*clone_node(t_list *room);
int			get_node_idx(t_lmdata *data, char *name);
void		check_adj(t_lmdata *data);
void		realloc_adj(t_lmdata *data);
size_t		ft_arr_len(void **arr);
void		ft_free_parr(void ***arr);
void		ft_realloc(void **mem, size_t old_size, size_t new_size);
t_lmdata	*new_data(int mds);
t_node		*new_node(char *line, int x, int y);
void		del_node(void *content, size_t content_size);
t_list		*new_room_node(char *name, int x, int y);
void		free_node(t_node **node);
void		print_path(t_lmdata *data);
void		save_path(t_lmdata *data, t_list **path);
void		bfs(t_lmdata *data, t_list *black_list);
void		wash_up_map(t_lmdata *data);
void		add_path_to_blacklist(t_list **black_list, t_list *path);
t_err 		*new_err(int err_code, void *extra, size_t extra_len);
t_pair		*ft_newpair(void *fst, size_t fst_size, void *scd, size_t scd_len);
void		ft_lstdelsafe(t_list **lst, void *data, int (*cmp)(void *cdata, void *data), void (*del)(void *content, size_t content_size));
void		del_link(t_lmdata *data, char *n1, char *n2);
char		*ft_strimplode(char **arr, int size, char *glue);
int			find_in_pinput(char **input, int size, char *line);

t_err		*parse_link(char *line, t_lmdata *data);
t_err		*parse_room(char *line, t_lmdata *data, int cmd_mode, t_pair *extra);
t_err		*parse_command(char *line, int *cmd_mode, t_pair *extra);

/*
** For tests
*/

void		print_rooms(t_list *elem);

#endif
