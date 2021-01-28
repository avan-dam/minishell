# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: salbregh <salbregh@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/01/27 17:37:19 by salbregh      #+#    #+#                  #
#    Updated: 2021/01/27 19:23:19 by ambervandam   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

SRCS =		main.c \
			builtins/echo.c \
			builtins/unset.c \
			builtins/pwd.c \
			builtins/env.c \
			builtins/export.c \
			builtins/cd.c \
			builtins/exit.c \
			list_utils/ft_lst_addback.c \
			list_utils/ft_lstclear.c \
			list_utils/ft_lstnew.c \
			list_utils/ft_lstprint.c \
			list_utils/ft_split_into_list.c \
			utils.c \
			replace_dolla.c \
			set_arrays.c \
			redir.c \
			newparser.c \
			execve.c \
			signal.c
			# exec.c \
			# exit_status.c \
			# parser.c \
			# delete unused_tlist.c
			# unused_tlists.c

FLAGS = 	-Wall -Werror -Wextra 

SEGFAULT =	-g -fsanitize=address

OFILES =	$(SRCS:.c=.o)

INCLUDES =	./get_next_line \
			./libft

all:		$(NAME)

$(NAME):	$(OFILES) $(INCLUDES)
			make -C get_next_line/
			cp get_next_line/libgnl.a .
			make -C libft/
			cp libft/libft.a .
			$(CC) -Lget_next_line -lgnl -Llibft -lft -o $(NAME) $(OFILES) $(FLAGS) $(SEGFAULT)
			
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
