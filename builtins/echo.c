/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:52:44 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/19 16:21:57 by ambervandam   ########   odam.nl         */
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
	if (string == NULL)
		return (0);
	string = ft_howmany_n(string, 0, 0);
	if (ft_strcmp(string, "") == 0)
		return (0);
	ft_putstr_fd(string, mini->stdout);
	free(string);
	return (0);
}

static int	check_n_argv(char *string, t_mini *mini)
{
	int		i;
	char	*tempptr;

	i = 0;
	if (string == NULL || ft_strcmp(string, "") == 0
		|| ft_strcmp(string, "-") == 0)
	{
		free(string);
		return (-1);
	}
	tempptr = string;
	string = ft_strtrim_backslash(tempptr, ' ');
	free(string);
	string = check_tokens(string, mini, 0, 6);
	if (string == NULL || ft_strcmp(string, "") == 0
		|| ft_strcmp(string, "-") == 0)
	{
		free(string);
		return (-1);
	}
	if (string[i] != '-')
	{
		free(string);
		return (-1);
	}
	i++;
	while (string[i] == 'n')
		i++;
	if (string[i] != '\0')
	{
		free(string);
		return (-1);
	}
	free(string);
	return (1);
}

static int	check_empty(char *string)
{
	int	i;

	i = 0;
	if (string == NULL || ft_strcmp(string, "") == 0)
		return (-1);
	while (string[i])
	{
		if (string[i] != ' ')
			return (0);
		i++;
	}
	return (-1);
}
static char	*ft_avs_into_string(t_base *ptr, int i, char *string, t_mini *mini)
{
	char	*tmp2;
	char	*tempptr;
	char	*tmp22;
	int		k;

	tmp2 = NULL;
	tempptr = ptr->av[i];
	while (check_n_argv(tempptr, mini) == 1)
	{
		free(ptr->av[i]);
		ptr->av[i] = ft_strdup("-n");
		i++;
		if (ptr->av[i] == NULL)
			break ;
		tempptr = ptr->av[i];
	}
	while (ptr->av[i])
	{
		if (!(ptr->av[i + 1]))
		{
			tempptr = ptr->av[i];
			if (ft_strcmp(ptr->av[i], "") != 0)
				free(ptr->av[i]);
			ptr->av[i] = ft_strtrim_backslash(tempptr, ' ');
		}
		tmp22 = check_tokens(ptr->av[i], mini, 0, 6);
		if ((check_empty(tmp22) == -1) && (numb_char(ptr->av[i], '$') > 0))
		{
			free(tmp22);
			tmp22 = ft_strdup("");
			if (!(ptr->av[i + 1]) && string && string[ft_strlen(string) - 1] == ' ')
			{
				k = ft_strlen(string) - 1;
				while (k >= 0)
				{
					if (string[k] == ' ')
						ft_memmove(&string[k], &string[k + 1], ft_strlen(string) - k);
					k--;
				}
			}
		}
		if (!(ptr->av[i + 1]) && (numb_char(ptr->av[i], '\\') > 0) && i == 1)
		{
			if (!(ptr->av[i + 1]) && tmp22 && tmp22[ft_strlen(tmp22) - 1] == ' ')
			{
				k = ft_strlen(tmp22) - 1;
				while (k >= 0)
				{
					if (tmp22[k] == ' ')
						ft_memmove(&tmp22[k], &tmp22[k + 1], ft_strlen(tmp22) - k);
					k--;
				}
			}
		}
		string = ft_strjoin(tmp2, tmp22);
		free(tmp22);
		free(tmp2);
		tmp2 = string;
		i++;
	}

	return (string);
}

int	ft_echo(t_base *ptr, t_mini *mini)
{
	char	*string;

	if ((ft_strcmp("", ptr->av[0]) == 0) || (ptr->av[1] == NULL))
	{
		mini->exit = 0;
		return (ft_putstr_fd("", mini->stdout));
	}
	string = ft_avs_into_string(ptr, 1, NULL, mini);
	mini->exit = 0;
	if (ft_strcmp(ptr->av[1], "-n") == 0)
		return (ft_echo_n(string, mini));
	if (string == NULL || ft_check_empty(string) == 1)
	{
		if (string == NULL || ft_strcmp("", string) == 0)
			free(string);
		return (ft_putchar_fd('\n', mini->stdout));
	}
	ft_putstr_fd(string, mini->stdout);
	free(string);
	return (ft_putchar_fd('\n', mini->stdout));
}
