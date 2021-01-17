# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: salbregh <salbregh@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/01/17 22:18:02 by salbregh      #+#    #+#                  #
#    Updated: 2021/01/17 22:18:04 by salbregh      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

SRCS =		builtins/echo.c \
			builtins/unset.c \
			builtins/pwd.c \
			builtins/env.c \
			builtins/export.c \
			builtins/cd.c \
			parser.c \
			utils.c \
			t_list.c \
			replace_dolla.c \
			exec.c \
			set_arrays.c \
			redir.c
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
