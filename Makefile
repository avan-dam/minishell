# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: avan-dam <avan-dam@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/12/03 17:24:32 by avan-dam      #+#    #+#                  #
#    Updated: 2020/12/04 17:47:54 by ambervandam   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

SRCS =		parser.c \
			echo.c \
			utils.c \
			export.c \
			ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c

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
