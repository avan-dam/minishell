/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   backslash_trimming.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/22 13:05:10 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/23 21:25:06 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_begin(const char *s1, char c)
{
	int		i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != c)
			return (i);
		i++;
	}
	return (i);
}

static int	ft_end(const char *s1, char c)
{
	int		i;

	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		if (s1[i] != c || i == 0 || s1[i - 1] == '\\')
			return (i);
		i--;
	}
	return (i);
}

char	*ft_strtrim_backslash(char const *s1, char c)
{
	int		i;
	int		begin;
	int		end;
	char	*newstr;

	if (s1 == NULL)
		return (NULL);
	begin = ft_begin(s1, c);
	end = ft_end(s1, c);
	if (begin > end)
		return (ft_strdup(""));
	newstr = (char *)malloc(sizeof(char) * (end - begin + 2));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (begin <= end)
	{
		newstr[i] = s1[begin];
		i++;
		begin++;
	}
	newstr[i] = '\0';
	return (newstr);
}
