# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: avan-dam <avan-dam@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/09 16:07:37 by avan-dam       #+#    #+#                 #
#    Updated: 2020/03/09 16:11:40 by avan-dam      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a

SRCS = get_next_line.c get_next_line_utils.c

LIB = get_next_line.o get_next_line_utils.o

INCLUDE = libgnl.h

all: $(NAME)

$(NAME): $(LIB)
	ar rc $(NAME) $(LIB)
	ranlib $(NAME)

%.o: %.c
	gcc -o $@ -c $< -Wall -Wextra -Werror

clean:
	/bin/rm -f $(LIB)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
