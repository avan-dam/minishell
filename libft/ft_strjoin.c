/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:10:14 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/19 16:38:37 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*return_strdup(char const *s1, char const *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (ft_strdup(""));
	if (s1 == NULL || ft_strcmp(s1, "") == 0)
		return (ft_strdup(s2));
	if (s2 == NULL || ft_strcmp(s2, "") == 0)
		return (ft_strdup(s1));
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*str;
	size_t		i;
	size_t		j;
	char		*dup;

	dup = return_strdup(s1, s2);
	if (dup != NULL)
		return (dup);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (0);
	i = 0;
	j = 0;
	while (i < ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
