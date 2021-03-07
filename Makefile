# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: salbregh <salbregh@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/01/29 23:26:43 by salbregh      #+#    #+#                  #
#    Updated: 2021/03/07 08:00:16 by ambervandam   ########   odam.nl          #
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
			builtins/signal.c \
			list_utils/ft_lst_addback.c \
			list_utils/ft_lstclear.c \
			list_utils/ft_lstnew.c \
			list_utils/ft_lstprint.c \
			list_utils/ft_split_into_list.c \
			parser_utils/utils.c \
			parser_utils/utils2.c \
			parser_utils/replace_specials.c \
			parser_utils/replace_dolla.c \
			parser_utils/replace_quote_backslash.c \
			parser_utils/redir.c \
			parser_utils/redir_adapt_array.c \
			parser_utils/redir_check_valid.c \
			parser_utils/parser.c \
			parser_utils/parser_av_list.c \
			parser_utils/parser_no_commands.c \
			execve/execve.c \
			leaks.c \
			execve/builtins.c
# lets delete the leaks.c
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
			$(CC) -Lget_next_line -lgnl -Llibft -lft -o $(NAME) $(OFILES) $(FLAGS)  
			#$(SEGFAULT)
			
%.o:		%.c
			gcc -Ilibft -Ignl $(FLAGS) -c $< -o $@

clean:
			/bin/rm -f $(OFILES)
			make clean -C get_next_line/
			make clean -C libft/

fclean:		clean
			/bin/rm -f get_next_line/libgnl.a
			/bin/rm -f libgnl.a
			/bin/rm -f libft/libft.a
			/bin/rm -f libft.a
			/bin/rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
