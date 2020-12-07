/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:14:36 by salbregh      #+#    #+#                 */
/*   Updated: 2020/11/15 16:14:41 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*ft_substr_gnl(char *s, unsigned int start, size_t l, int call)
{
	char			*str;
	unsigned int	d;
	int				i;

	d = start + l;
	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strl(s))
		return (ft_strdup_gnl(""));
	str = (char *)malloc(sizeof(char) * d > ft_strl(s)\
			? (ft_strl(s) - start + 1) : (l + 1));
	if (str == NULL)
		return (ft_free_me(&str));
	while (start < d && s[start] != '\0')
	{
		str[i] = s[start];
		i++;
		start++;
	}
	if (call > 0)
		free(s);
	str[i] = '\0';
	return (str);
}

char			*ft_strjoin_gnl(char *s1, char *s2)
{
	char		*str;
	size_t		i;

	i = 0;
	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strl(s1) + ft_strl(s2) + 1));
	if (str == NULL)
		return (ft_free_me(&str));
	while (i < ft_strl(s1))
	{
		str[i] = s1[i];
		i++;
	}
	while (i < ft_strl(s2) + ft_strl(s1))
	{
		str[i] = s2[i - ft_strl(s1)];
		i++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

char			*ft_strdup_gnl(const char *s1)
{
	size_t		i;
	char		*newstr;

	i = 0;
	newstr = (char *)malloc(sizeof(*newstr) * (ft_strl(s1) + 1));
	if (newstr == NULL)
		return (NULL);
	while (i <= ft_strl(s1))
	{
		newstr[i] = s1[i];
		i++;
	}
	return ((char *)newstr);
}

size_t			ft_strl(const char *s)
{
	size_t		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char			*ft_free_me(char **s)
{
	if (*s == NULL)
		free(s);
	return (NULL);
}
