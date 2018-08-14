# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Lem-in.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/07 14:35:08 by oevtushe          #+#    #+#              #
#    Updated: 2018/08/08 18:07:14 by oevtushe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LN_NAME				:= lem-in

LN_SRCS_DIR			:= srcs
LN_DEPS_DIR			:= includes
LN_ERRS_DIR			:= $(LN_SRCS_DIR)/errors
LN_OBJS_DIR			:= objs

FT_DIR				:= $(LN_SRCS_DIR)/libft
FTP_DIR				:= $(LN_SRCS_DIR)/ft_printf
include				$(FT_DIR)/Pretty.mk
include 			$(FTP_DIR)/Libftp.mk

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
					   new_err.c					\
					   err_room_no_y.c

LN_ERRS				:= $(LN_ERRF:%=$(LN_ERRS_DIR)/%)

LN_SRCF				:= main.c					\
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
					   pdecode_paths.c			\
					   del_link.c				\
					   del_utils.c				\
					   read_data.c				\
					   copy_rebased_paths.c		\
					   copy_simple_paths.c		\
					   del_simple_paths.c		\
					   node_utils.c				\
					   map_path_list.c			\
					   del_int.c				\
					   free_lmdata.c			\
					   print_ants_helpers.c		\
					   read_errs_wrap.c			\
					   comparators.c			\
					   get_paths.c				\
					   print_ants.c				\
					   move_ants.c				\
					   parse_room_hlp.c			\
					   parse_room.c				\
					   rebase_paths.c			\
					   gen_color.c				\
					   read_ants.c				\
					   mk_output.c				\
					   new_data.c

LN_SRCS				:= $(LN_SRCF:%=$(LN_SRCS_DIR)/%) $(LN_ERRS)
LN_DEPS				:= $(LN_DEPF:%=$(LN_DEPS_DIR)/%)
LN_OBJS				:= $(LN_SRCF:%.c=$(LN_OBJS_DIR)/%.o) $(LN_ERRS:$(LN_SRCS_DIR)/%.c=$(LN_OBJS_DIR)/%.o)
LN_ALL_DEPS			:= $(FTP_ALL_DEPS) $(LN_DEPS)
LN_ALL_DEPS_DIRS	:= $(FTP_ALL_DEPS_DIRS) $(LN_DEPS_DIR)
LN_ALL_OBJS			:= $(FTP_ALL_OBJS) $(LN_OBJS)
LN_ALL_OBJS_DIRS	:= $(LN_OBJS_DIR) $(LN_OBJS_DIR)/$(LN_ERRS_DIR:$(LN_SRCS_DIR)/%=%)
LN_ALL_EXTRA_LIBS	:= $(FTP_NAME)
