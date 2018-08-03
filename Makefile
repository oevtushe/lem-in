# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/12 10:30:58 by oevtushe          #+#    #+#              #
#    Updated: 2018/08/03 16:28:22 by oevtushe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LN_NAME				:= lem-in

LN_SRCS_DIR			:= srcs
LN_DEPS_DIR			:= includes
LN_ERRS_DIR			:= $(LN_SRCS_DIR)/errors
LN_OBJS_DIR			:= objs
LN_OBJS_DIRS		:= $(LN_OBJS_DIR) $(LN_OBJS_DIR)/$(LN_ERRS_DIR:$(LN_SRCS_DIR)/%=%)

FTM_DIR				:= $(LN_SRCS_DIR)/libftmulti
FT_DIR				:= $(FTM_DIR)/libft
GNL_DIR				:= $(FTM_DIR)/gnl
FTP_DIR				:= $(FTM_DIR)/ft_printf
include 			$(FTM_DIR)/Libftmulti.mk
include				$(FT_DIR)/Pretty.mk

LN_ERRF				:= error_handler.c				\
					   err_empty_line.c				\
					   err_cmnt_after_cmd.c			\
					   err_ants_inv_num.c			\
					   err_cmd_bad_using.c			\
					   err_cmd_double_end.c			\
					   err_cmd_double_start.c		\
					   err_data_empty.c				\
					   err_data_no_end.c			\
					   err_data_no_start.c			\
					   err_data_no_start_end.c		\
					   err_data_no_path.c			\
					   err_link_double.c			\
					   err_link_extra_chrs.c		\
					   err_link_not_existing_room.c	\
					   err_link_self.c				\
					   err_link_spaces.c			\
					   err_link_uns_data.c			\
					   err_room_bad_coord.c			\
					   err_room_bad_name.c			\
					   err_room_bad_x.c				\
					   err_room_bad_y.c				\
					   err_room_double_def.c		\
					   err_room_extra_parms.c		\
					   err_room_no_xy.c				\
					   err_room_spaces.c			\
					   err_coords_double_def.c		\
					   li_cmd_double.c				\
					   cmp_simple.c					\
					   new_err.c					\
					   err_room_no_y.c

LN_ERRS				:= $(LN_ERRF:%=$(LN_ERRS_DIR)/%)

LN_SRCF				:= main.c					\
					   ft_realloc.c				\
					   new_node.c				\
					   print_rooms.c			\
					   del_node.c				\
					   reallocators.c			\
					   get_node_idx.c			\
					   new_room_node.c			\
					   add_link.c				\
					   clone_node.c				\
					   print_path.c				\
					   save_path.c				\
					   bfs.c					\
					   wash_up_map.c			\
					   parsers.c				\
					   add_path_to_blacklist.c	\
					   check_overlapping.c		\
					   pdecode_paths.c			\
					   del_link.c				\
					   backtracking.c			\
					   add_node_to_blacklist.c	\
					   ft_qsarr.c				\
					   ft_lsttoarr.c			\
					   ft_lstnew_cc.c			\
					   ft_arrtolst.c			\
					   del_utils.c				\
					   ft_freepa.c				\
					   ft_freepa_sd.c			\
					   ft_argsparser.c			\
					   cmp_lst_str.c			\
					   read_data.c				\
					   new_data.c
LN_DEPF				:= lem_in.h lm_errs.h

LN_SRCS				:= $(LN_SRCF:%=$(LN_SRCS_DIR)/%) $(LN_ERRS)
LN_DEPS				:= $(LN_DEPF:%=$(LN_DEPS_DIR)/%)
LN_OBJS				:= $(LN_SRCF:%.c=$(LN_OBJS_DIR)/%.o) $(LN_ERRS:$(LN_SRCS_DIR)/%.c=$(LN_OBJS_DIR)/%.o)

CC					:= gcc
CFLAGS				:= $(DEBUG) -Wall -Werror -Wextra -g
RM					:= rm -rf
MFLAGS				:= --no-print-directory -C
IFLAGS				:= -I$(LN_DEPS_DIR) -I$(FT_DEPS_DIR) -I$(GNL_DIR) -I$(FTP_DEPS_DIR)

all: $(LN_NAME)

$(LN_NAME): $(LN_OBJS)
	@$(call EXEC_P,$@)
	@$(CC) $(CFLAGS) -o $(LN_NAME) $^ $(FTM_NAME)

$(LN_OBJS_DIR)/%.o: $(LN_SRCS_DIR)/%.c $(LN_DEPS) $(FTM_NAME)
	@$(call COMPILE_P,$@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(IFLAGS)

$(LN_OBJS): |$(LN_OBJS_DIRS)

$(LN_OBJS_DIRS):
	@$(call DIR_CREATE_P,$@)
	@mkdir $@

$(FTM_NAME): $(FTM_SRCS) $(FTM_DEPS)
	@$(MAKE) RPTH=srcs $(MFLAGS) $(FTM_DIR)

clean:
	@$(MAKE) clean $(MFLAGS) $(FTM_DIR)
	@$(RM) $(LN_OBJS_DIR)

fclean: clean
	@$(MAKE) fclean $(MFLAGS) $(FTM_DIR)
	@$(RM) $(LN_OBJS_DIR)

re: fclean
	@$(MAKE)
