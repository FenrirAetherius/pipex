# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrozniec <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/27 16:57:15 by mrozniec          #+#    #+#              #
#    Updated: 2021/11/27 16:57:18 by mrozniec         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = pipex

FLAGS = -Wall -Wextra -Werror

SRC =	ft_split.c\
		ft_strjoin.c\
		main.c\
		utils.c

OBJ =	$(SRC:.c=.o)

all: $(NAME)

$(NAME):	$(OBJ) $(HEADER)
			@cc $(FLAGS) -o$(NAME) $(OBJ)

%.o: %.c	$(HEADER)
			@cc -o $@ -c $< $(FLAGS)

.PHONY: clean fclean re all

clean:
		@/bin/rm $(OBJ)

fclean:	clean
		@/bin/rm -rf $(NAME)

re:	fclean all