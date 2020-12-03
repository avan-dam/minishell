 /* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 17:47:54 by avan-dam       #+#    #+#                */
/*   Updated: 2019/12/22 11:54:24 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libgnl.h"

int		ft_len(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int		ft_no_new_line(char *storage)
{
	int	i;
	int	length;

	if (storage == NULL)
		return (0);
	if (storage[0] == '\n' && storage)
		return (-1);
	i = 0;
	length = ft_len(storage);
	while (storage[i] && i <= length)
	{
		if (storage[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

char	*ft_strdupp(char *s1)
{
	size_t	s;
	char	*ptr;
	int		i;

	s = ft_len(s1);
	i = 0;
	ptr = (char *)malloc(sizeof(char) * (s + 1));
	if (ptr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_substrr(char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	j;
	size_t	slen;

	j = 0;
	if (s == NULL)
		return (NULL);
	slen = ft_len(s);
	if (start > slen)
		return (ft_strdupp(""));
	if (start + len > slen)
		len = slen - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	while ((j < len) && (s[start] != '\0'))
	{
		substr[j] = s[start];
		j++;
		start++;
	}
	substr[j] = '\0';
	return (substr);
}

char	*ft_strjoinn(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if ((s2 == 0 && s1 == 0) || s2 == 0)
		return (NULL);
	if (s1 == 0)
		return (ft_strdupp(s2));
	str = (char *)malloc(sizeof(char) * (ft_len(s1) + ft_len(s2) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
