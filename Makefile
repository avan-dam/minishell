# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: avan-dam <avan-dam@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/12/06 12:33:02 by avan-dam      #+#    #+#                  #
#    Updated: 2020/12/09 20:03:19 by ambervandam   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

SRCS =		parser.c \
			echo.c \
			utils.c \
			export.c \
			t_list.c \
			cd.c \
			replace_dolla.c \
			unset.c \
			pwd.c \
			env.c
# unused_tlists.c

FLAGS = 	-Wall -Werror -Wextra
#  -g -fsanitize=address

OFILES =	$(SRCS:.c=.o)

INCLUDES =	./get_next_line \
			./libft

all:		$(NAME)

$(NAME):	$(OFILES) $(INCLUDES)
			make -C get_next_line/
			cp get_next_line/libgnl.a .
			make -C libft/
			cp libft/libft.a .
			$(CC) -Lget_next_line -lgnl -Llibft -lft -o $(NAME) $(OFILES) $(FLAGS)
			
%.o:		%.c
			gcc -Ilibft -Ignl $(FLAGS) -c $< -o $@

clean:
			/bin/rm -f $(OFILES)
			make clean -C get_next_line/
			make clean -C libft/

fclean:		clean
			/bin/rm -f gnl/libgnl.a
			/bin/rm -f libgnl.a
			/bin/rm -f $(NAME)
			# doenst remove the lib in the libft and GNL

re:			fclean all

.PHONY:		all clean fclean re
