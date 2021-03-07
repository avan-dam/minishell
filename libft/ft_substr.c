/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 12:37:13 by avan-dam      #+#    #+#                 */
/*   Updated: 2021/02/21 20:35:40 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	j;
	size_t	slen;

	j = 0;
	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
		return (ft_strdup(""));
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
