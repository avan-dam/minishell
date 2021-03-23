# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: salbregh <salbregh@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/01/29 23:26:43 by salbregh      #+#    #+#                  #
#    Updated: 2021/03/23 21:56:11 by ambervandam   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

SRCS =		main.c \
			builtins/echo.c \
			builtins/echo_more.c \
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
			list_utils/delete_node.c \
			parser_utils/utils.c \
			parser_utils/utils2.c \
			parser_utils/utils3.c \
			parser_utils/replace_specials.c \
			parser_utils/replace_dolla.c \
			parser_utils/replace_quote_backslash.c \
			parser_utils/redir.c \
			parser_utils/redir_adapt_array.c \
			parser_utils/redir_check_valid.c \
			parser_utils/parser.c \
			parser_utils/parser_av_list.c \
			parser_utils/parser_no_commands.c \
			parser_utils/parser_commands.c \
			parser_utils/backslash_trimming.c \
			parser_utils/fill_arguments_list.c \
			execve/execve.c \
			execve/sort_struct.c \
			execve/builtins.c

FLAGS = 	-Wall -Werror -Wextra 

OFILES =	$(SRCS:.c=.o)

INCLUDES =	./get_next_line/get_next_line.h \
			./libft/libft.h \
			minishell.h

EXTE_LIBS = ./get_next_line/libgnl.a \
			./libft/libft.a 

CC		=	gcc

all:		$(NAME)

$(NAME):	$(OFILES) $(INCLUDES)
			make -C get_next_line/
			cp get_next_line/libgnl.a .
			make -C libft/
			cp libft/libft.a .
			$(CC) -Lget_next_line -lgnl -Llibft -lft -o $(NAME) $(OFILES) $(FLAGS) $(EXTE_LIBS)
			
%.o:		%.c $(INCLUDES)
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
