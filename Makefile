# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/12 10:30:58 by oevtushe          #+#    #+#              #
#    Updated: 2018/08/07 19:34:54 by oevtushe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include				Lem-in.mk
include				$(FT_DIR)/Templates.mk

CFLAGS	+= -g

all: $(LN_NAME)

$(eval $(call BINARY_template2,LN,FTP))
$(eval $(call EXTRALIB_template2,FTP,libftprintf,all))
$(eval $(call BASIC_template,LN))

clean:
	@$(MAKE) clean $(MFLAGS) $(FTP_DIR)
	@$(RM) $(LN_OBJS_DIR)

fclean: clean
	@$(MAKE) fclean $(MFLAGS) $(FTP_DIR)
	@$(RM) $(LN_OBJS_DIR)
