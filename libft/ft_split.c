/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:09:53 by salbregh      #+#    #+#                 */
/*   Updated: 2020/11/15 16:09:54 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_strings(const char *s, char c)
{
	int		strings;
	int		i;

	strings = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 || s[i] == c) && s[i + 1] != c && s[i + 1] != '\0')
			strings++;
		i++;
	}
	return (strings);
}

static int		ft_str_len(char const *s, int i, char c)
{
	int	len;

	len = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static int		ft_free_all(int word, int strings, char **strarray)
{
	if (!(strarray[word]))
	{
		while (strings != 0)
		{
			strings--;
			if (strarray[strings])
				free(strarray[strings]);
		}
		free(strarray);
		return (0);
	}
	return (1);
}

static char		**ft_fill_strarray(char const *s, char c,
				char **strarray, int strings)
{
	int	i;
	int	word;
	int	position;

	i = 0;
	word = 0;
	while (s[i] != '\0' && word < strings)
	{
		position = 0;
		while (s[i] == c)
			i++;
		strarray[word] = (char*)malloc(sizeof(char) * ft_str_len(s, i, c) + 1);
		if (!(ft_free_all(word, strings, strarray)))
			return (0);
		while ((s[i] != c) && (s[i] != '\0'))
		{
			strarray[word][position] = s[i];
			i++;
			position++;
		}
		strarray[word][position] = '\0';
		word++;
	}
	strarray[word] = NULL;
	return (strarray);
}

char			**ft_split(const char *s, char c)
{
	char	**strarray;
	int		strings;

	if (s == 0)
		return (NULL);
	strings = ft_count_strings(s, c);
	strarray = (char**)malloc(sizeof(char*) * (strings + 1));
	if (strarray == NULL)
		return (NULL);
	ft_fill_strarray(s, c, strarray, strings);
	return (strarray);
}
