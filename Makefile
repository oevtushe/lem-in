# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/12 10:30:58 by oevtushe          #+#    #+#              #
#    Updated: 2018/07/09 16:20:30 by oevtushe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LN_NAME				:= lem-in

LN_SRCS_DIR			:= srcs
LN_OBJS_DIR			:= objs
LN_DEPS_DIR			:= includes

FTM_DIR				:= $(LN_SRCS_DIR)/libftmulti
FT_DIR				:= $(FTM_DIR)/libft
GNL_DIR				:= $(FTM_DIR)/gnl
FTP_DIR				:= $(FTM_DIR)/ft_printf
include 			$(FTM_DIR)/Libftmulti.mk
include				$(FT_DIR)/Pretty.mk

LN_SRCF				:= main.c				\
					   ft_arr_len.c			\
					   ft_free_parr.c		\
					   ft_realloc.c			\
					   new_node.c			\
					   print_rooms.c		\
					   del_node.c			\
					   realloc_adj.c		\
					   get_node_idx.c		\
					   new_room_node.c		\
					   add_link.c			\
					   ft_lstcontains.c		\
					   ft_lstcontains.c		\
					   ft_arrcontains.c		\
					   ft_new_pair.c		\
					   ft_lstdequeue.c		\
					   clone_node.c			\
					   new_data.c
LN_DEPF				:= lem_in.h

LN_SRCS				:= $(LN_SRCF:%=$(LN_SRCS_DIR)/%)
LN_DEPS				:= $(LN_DEPF:%=$(LN_DEPS_DIR)/%)
LN_OBJS				:= $(LN_SRCF:%.c=$(LN_OBJS_DIR)/%.o)

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

$(LN_OBJS): |$(LN_OBJS_DIR)

$(LN_OBJS_DIR):
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
