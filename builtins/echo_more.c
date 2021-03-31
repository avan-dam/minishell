/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_more.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 17:21:47 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/31 13:26:33 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_empty(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || ft_strcmp(str, "") == 0)
		return (-1);
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (-1);
}

int	free_return(char *str)
{
	free(str);
	return (-1);
}

void	check_last_arg(t_base *ptr, int i)
{
	char	*tempptr;

	tempptr = ptr->av[i];
	ptr->av[i] = ft_strtrim_backslash(tempptr, ' ');
	free(tempptr);
}

static char	*ft_howmany_n(char *str, int i, int j)
{
	if (ft_strcmp(str, "-n") == 0)
		return (ft_substr(str, 3, ft_strlen(str) - 3));
	while (str[i] != '\0')
	{
		j = i;
		if (str[i] != '-')
			return (ft_substr(str, j, ft_strlen(str) - j));
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] != ' ')
			return (ft_substr(str, j, ft_strlen(str) - j));
		i++;
	}
	return ("");
}

int	ft_echo_n(char *str, t_mini *mini)
{
	char	*tmp;

	if (str == NULL)
		return (0);
	if (ft_strcmp("", str) == 0)
	{
		str = ft_strdup("a");
		return (0);
	}
	tmp = str;
	str = ft_howmany_n(tmp, 0, 0);
	free(tmp);
	if (ft_strcmp(str, "") == 0)
		return (0);
	ft_putstr_fd(str, mini->stdout);
	free(str);
	return (0);
}
