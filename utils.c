/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 12:06:37 by ambervandam   #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2020/12/04 18:57:13 by ambervandam   ########   odam.nl         */
=======
/*   Updated: 2020/12/05 19:04:50 by salbregh      ########   odam.nl         */
>>>>>>> origin/sannebranch
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libgnl.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;
	i = 0;
	ptr = b;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	write(1, s, ft_len(s));
}
<<<<<<< HEAD


int	    ft_strchr_numb(const char *s, int c)
{
	int		length;
	int		i;

	i = 0;
	length = ft_len(s);
	if ((char)c == '\0')
		return (length);
	while (i < length)
	{
		if (s[i] == (char)c)
		{
			return (i);
		}
		i++;
	}
	return (0);
}
=======
>>>>>>> origin/sannebranch
