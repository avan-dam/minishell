/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/07 15:54:25 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/07 16:11:21 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		ft_howmany_n(char *string, int i, int j, int l)
{
	while (string[i] != '\0')
	{
		l++;
		j = i;
		if (string[i] != '-')
			return (-1);
		i++;
		while (string[i] == 'n')
			i++;
		if (string[i] == '\0')
			return (1);
		if (string[i] != ' ')
		{
			string = ft_substr(string, j, ft_strlen(string) - j);
			return (2);
		}
		i++;
	}
	return (0);
}

static int		ft_echo_n(char *string)
{
	int	i;
	int	j;

	if (string == NULL)
		return (0);
	if ((j = ft_howmany_n(string, 0, 0, 0)) == 2)
		return (2);
	if (j != 2)
	{
		i = ft_len(string) - 3;
		string = ft_substrr(string, 3, i);
	}
	string = ft_strtrim(string, " ");
	ft_putstr(string);
	return (0);
}

static int		ft_check_empty(char *string)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (ft_strcmp(string, "") == 0)
		return (1);
	while (string[i] != '\0')
	{
		if (string[i] == ' ')
			j++;
		i++;
	}
	if (i == j)
		return (1);
	return (0);
}

int				ft_echo(char *string)
{
	if (string == NULL)
		return (ft_putchar('\n'));
	if (ft_check_empty(string) == 1)
		return (ft_putchar('\n'));
	else if ((string[0] == '-') && (string[1] == 'n') &&
	((string[2] == ' ') || (string[2] == '\0') || (string[2] == 'n')))
	{
		if (ft_echo_n(string) != 2)
			return (0);
	}
	string = ft_strtrim(string, " ");
	ft_putstr(string);
	return (ft_putchar('\n'));
}
