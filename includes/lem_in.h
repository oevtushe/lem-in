/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:31:45 by oevtushe          #+#    #+#             */
/*   Updated: 2018/07/24 10:44:06 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "lm_errs.h"

typedef struct	s_rdata
{
	int 	cmd_mode;
	int		data_type;
	t_err	*err;
}				t_rdata;

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

void		pdecode_paths(t_lmdata *data, t_list *paths);
int			check_overlapping(t_list *paths, t_list *path);
//int			backtracking(t_lmdata *data, t_pair *paths, int root);
t_err		*add_link(t_lmdata *data, char *fst, char *scd);
t_list		*clone_node(t_list *room);
int			get_node_idx(t_lmdata *data, char *name);
void		check_adj(t_lmdata *data);
void		realloc_adj(t_lmdata *data);
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
void		del_link(t_lmdata *data, char *n1, char *n2);

t_err		*parse_link(char *line, t_lmdata *data);
t_err		*parse_room(char *line, t_lmdata *data, int cmd_mode, t_pair *extra);
t_err		*parse_command(char *line, int *cmd_mode, t_pair *extra);

/*
** For tests
*/

void		print_rooms(t_list *elem);

#endif
