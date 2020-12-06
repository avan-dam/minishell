# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: avan-dam <avan-dam@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/12/06 12:33:02 by avan-dam      #+#    #+#                  #
#    Updated: 2020/12/06 13:59:38 by salbregh      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

SRCS =		parser.c \
			echo.c \
			utils.c \
			export.c \
			t_list.c \
			t_list_more.c \
			cd.c \
			pwd.c

FLAGS = 	-Wall -Werror -Wextra

OFILES =	$(SRCS:.c=.o)

INCLUDES =	./gnl \
			./libft

all:		$(NAME)

$(NAME):	$(OFILES) $(INCLUDES)
			make -C gnl/
			cp gnl/libgnl.a .
			make -C libft/
			cp libft/libft.a .
			$(CC) -Lgnl -lgnl -Llibft -lft -o $(NAME) $(OFILES) $(FLAGS)
			
%.o:		%.c
			gcc -Ilibft -Ignl $(FLAGS) -c $< -o $@

clean:
			/bin/rm -f $(OFILES)
			make clean -C gnl/

fclean:		clean
			/bin/rm -f gnl/libgnl.a
			/bin/rm -f libgnl.a
			/bin/rm -f $(NAME)

re:			fclean all

.PHONY: all clean fclean re
