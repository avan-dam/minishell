# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: avan-dam <avan-dam@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/12/03 17:24:32 by avan-dam      #+#    #+#                  #
<<<<<<< HEAD
#    Updated: 2020/12/04 17:32:44 by salbregh      ########   odam.nl          #
=======
#    Updated: 2020/12/04 18:11:14 by ambervandam   ########   odam.nl          #
>>>>>>> origin/env
#                                                                              #
# **************************************************************************** #

NAME =		minishell

SRCS =		parser.c \
			echo.c \
			utils.c \
			export.c \
			t_list.c \
			t_list_more.c 

FLAGS = 	-Wall -Werror -Wextra -O3

OFILES =	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OFILES)
			make -C gnl/
			cp gnl/libgnl.a .
			gcc -Lgnl -lgnl -o $(NAME) $(OFILES) $(FLAGS)
%.o:		%.c
			gcc -Ignl $(FLAGS) -c $< -o $@

clean:
			/bin/rm -f $(OFILES)
			make clean -C gnl/

fclean:		clean
			/bin/rm -f gnl/libgnl.a
			/bin/rm -f libgnl.a
			/bin/rm -f $(NAME)

re:			fclean all

.PHONY: all clean fclean re
