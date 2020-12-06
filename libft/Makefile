# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sannealbreghs <sannealbreghs@student.co      +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/21 13:28:31 by sannealbreg   #+#    #+#                  #
#    Updated: 2020/12/06 13:48:53 by salbregh      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRCS	=	./ft_memset.c \
			./ft_bzero.c \
			./ft_memcpy.c \
			./ft_memccpy.c \
			./ft_memmove.c \
			./ft_memchr.c \
			./ft_memcmp.c \
			./ft_strlen.c \
			./ft_strlcpy.c \
			./ft_strlcat.c \
			./ft_strchr.c \
			./ft_strrchr.c \
			./ft_isalnum.c \
			./ft_isalpha.c \
			./ft_isascii.c \
			./ft_isdigit.c \
			./ft_isprint.c \
			./ft_tolower.c \
			./ft_toupper.c \
			./ft_strncmp.c \
			./ft_strnstr.c \
			./ft_atoi.c \
			./ft_calloc.c \
			./ft_strdup.c \
			./ft_substr.c \
			./ft_strjoin.c \
			./ft_putchar_fd.c \
			./ft_putstr_fd.c \
			./ft_putendl_fd.c \
			./ft_putnbr_fd.c \
			./ft_strmapi.c \
			./ft_strtrim.c \
			./ft_itoa.c \
			./ft_split.c \
			./ft_strstr.c

LIB		=	$(SRCS:.c=.o)

INCL	=	libft.h

CFLAGS	=	-Wall -Werror -Wextra

all:	$(NAME)

$(NAME): $(LIB)
			ar rc $(NAME) $(LIB)
			ranlib $(NAME)

%.o: %.c
			gcc -o $@ -c $< $(CFLAGS)

clean:
			@/bin/rm -f $(LIB)

fclean:	clean
			@/bin/rm -f $(NAME)

re: fclean all
