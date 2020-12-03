/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/03 17:24:36 by avan-dam      #+#    #+#                 */
/*   Updated: 2020/12/03 18:18:57 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libgnl.h"
#include "minishell.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		check_liney(char **liney)
{
	if (ft_strcmp(*liney, "echo") == 0)
		printf("I got an echo baby");
	else if (ft_strcmp(*liney, "cd") == 0)
		printf("I got an cd baby");
	else if (ft_strcmp(*liney, "pwd") == 0)
		printf("I got a PWD baby");
	else if (ft_strcmp(*liney, "export") == 0)
		printf("I got an export baby");
	else if (ft_strcmp(*liney, "unset") == 0)
		printf("I got an UNSNET baby");
	else if (ft_strcmp(*liney, "env") == 0)
		printf("I got an ENV baby");
	else if (ft_strcmp(*liney, "exit") == 0)
	{
		printf("I got an exit baby");
		liney = NULL;
		return (-1);
	}
	else
		printf("I do not recgonise the input entered[%s]", *liney);
	liney = NULL;
	return (0);
}

int		main(void)
{
	char	*line;
	int		liney;

	while (1)
	{
		liney = get_next_line(1, &line);
		if (liney == -1)
			printf("error");
		if (check_liney(&line) == -1)
			return (0);
	}
	return (0);
}

// USE FORK AND WAIT

