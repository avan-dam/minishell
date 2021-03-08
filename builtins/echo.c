/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:52:44 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/07 18:37:02 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_howmany_n(char *string, int i, int j)
{
	if (ft_strcmp(string, "-n") == 0)
		return (ft_substr(string, 3, ft_strlen(string) - 3));
	while (string[i] != '\0')
	{
		j = i;
		if (string[i] != '-')
			return (ft_substr(string, j, ft_strlen(string) - j));
		i++;
		while (string[i] == 'n')
			i++;
		if (string[i] != ' ')
			return (ft_substr(string, j, ft_strlen(string) - j));
		i++;
	}
	return ("");
}

static int	ft_echo_n(char *string, t_mini *mini)
{
	char	*tmp;

	if (string == NULL)
		return (0);
	string = ft_howmany_n(string, 0, 0);
	tmp = string;
	if (ft_strcmp(tmp, "") == 0)
		return (0);
	string = ft_strtrim(tmp, " ");
	ft_putstr_fd(string, mini->stdout);
	free(string);
	free(tmp);
	mini->exit = 0;
	return (0);
}

static int	ft_check_empty(char *string)
{
	int	i;
	int	j;

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
	{
		free(string);
		return (1);
	}
	return (0);
}

static char	*ft_avs_into_string(t_base *ptr, int i, char *string)
{
	char	*tmp;

	tmp = ft_strdup("");
	while (ptr->av[i])
	{
		string = ft_strjoin(tmp, ptr->av[i]);
		free(tmp);
		if (i + 1 != ptr->size)
		{
			if (ptr->av[i + 1] && ptr->av[i + 1][0] != '>'
				&& ptr->av[i + 1][0] != '<')
			{
				tmp = ft_strdup(string);
				free(string);
				string = ft_strjoin(tmp, " ");
				free(tmp);
			}
		}
		tmp = string;
		i++;
	}
	return (string);
}

int	ft_echo(t_base *ptr, t_mini *mini)
{
	char	*string;
	char	*tmp;

	mini->exit = 0;
	if (ft_strcmp("", ptr->av[0]) == 0)
		return (ft_putstr_fd("", mini->stdout));
	string = ft_avs_into_string(ptr, 1, NULL);
	if (string == NULL || ft_check_empty(string) == 1)
	{
		if (string == NULL)
			free(string);
		return (ft_putchar_fd('\n', mini->stdout));
	}
	if ((string[0] == '-') && (string[1] == 'n')
		&& ((string[2] == ' ') || (string[2] == '\0') || (string[2] == 'n')))
		return (ft_echo_n(string, mini));
	tmp = string;
	string = ft_strtrim(tmp, " ");
	ft_putstr_fd(string, mini->stdout);
	free(string);
	free(tmp);
	return (ft_putchar_fd('\n', mini->stdout));
}
