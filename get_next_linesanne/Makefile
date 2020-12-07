# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: salbregh <salbregh@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/05/11 14:36:38 by salbregh      #+#    #+#                  #
#    Updated: 2020/06/25 15:02:23 by salbregh      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		libgnl.a

SRCS =		get_next_line.c \
			get_next_line_utils.c

LIB =		$(SRCS:.c=.o)

INCLUDE =	get_next_line.h

FLAGS =		-Wall -Werror -Wextra

all:		$(NAME)

$(NAME):	$(LIB)
			ar rc $(NAME) $(LIB)
			ranlib $(NAME)

%.o: %.c
			gcc -o $@ -c $< $(FLAGS)

clean:
			/bin/rm -f $(LIB)

fclean:		clean
			/bin/rm -f $(NAME)

re:			fclean all
