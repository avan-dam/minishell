/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 17:59:22 by avan-dam       #+#    #+#                */
/*   Updated: 2019/12/20 17:56:18 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

int		get_next_line(int fd, char **line);
int		ft_len(const char *s);
char	*ft_strdupp(char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_substrr(char *s, unsigned int start, size_t len);
char	*ft_strjoinn(char *s1, char *s2);
int		ft_no_new_line(char *storage);

#endif
