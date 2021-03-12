/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:52:44 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/12 16:54:39 by ambervandam   ########   odam.nl         */
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

static int	check_n_argv(char *string, t_mini *mini)
{
	int		i;
	char	*tempptr;

	i = 0;
	if (string == NULL || ft_strcmp(string, "") == 0 || ft_strcmp(string, "-") == 0)
		return(-1);
	tempptr = string;
	string = ft_strtrim_backslash(tempptr, ' ');
	free(tempptr);
	string = mem_check_tkns(string, mini, 0 , 6);
	if (string == NULL || ft_strcmp(string, "") == 0 || ft_strcmp(string, "-") == 0)
		return(-1);
	if (string[i] != '-')
		return(-1);
	i++;
	while (string[i] == 'n')
		i++;
	if (string[i] != '\0')
		return (-1);
	return (1);
}

static char	*ft_avs_into_string(t_base *ptr, int i, char *string2, t_mini *mini)
{
	char	*tmp;
	char	*tmp2;
	char	*string;
	char	*tempptr;
	char	*tmp22;

	tmp = ft_strdup("");
	tmp2 = ft_strdup("");
	string = NULL;
	tempptr = ft_strdup(ptr->av[i]);
	while (check_n_argv(tempptr, mini) == 1)
	{
		free(ptr->av[i]);
		ptr->av[i] = ft_strdup("-n");
		i++;
		if (ptr->av[i] == NULL)
			break ;
		free(tempptr);
		tempptr = ft_strdup(ptr->av[i]);
	}
	free(tempptr);
	while (ptr->av[i])
	{
		if (ptr->av[i][0] == '$' || !(ptr->av[i+1]))
		{
			tempptr = ft_strdup(ptr->av[i]);
			free(ptr->av[i]);
			ptr->av[i] = ft_strtrim_backslash(tempptr, ' ');
			free(tempptr);
		}
		string = ft_strjoin(tmp, ptr->av[i]);
		free(tmp);
		tmp22 = check_tokens(ptr->av[i], mini, 0 , 6);
		string2 = ft_strjoin(tmp2, tmp22);
		free(tmp22);
		free(tmp2);
		tmp = string;
		tmp2 = string2;
		i++;
	}
	free(string);
	if (string2 && tmp && string2[ft_strlen(string2) - 1] == ' ' && tmp[ft_strlen(tmp) - 1] != '\'' && tmp[ft_strlen(tmp) - 1] != '"')
	{
		tmp = string2;
		string2 = ft_substr(tmp, 0, ft_strlen(string2) - 1);
		free(tmp);
	}
	return (string2);
}

int	ft_echo(t_base *ptr, t_mini *mini)
{
	char	*string;

	mini->exit = 0;
	if ((ft_strcmp("", ptr->av[0]) == 0) || (ptr->av[1] == NULL))
		return (ft_putstr_fd("", mini->stdout));
	string = ft_avs_into_string(ptr, 1, NULL, mini);
	if (string == NULL || ft_check_empty(string) == 1)
	{
		if (string == NULL)
			free(string);
		return (ft_putchar_fd('\n', mini->stdout));
	}
	if (ft_strcmp(ptr->av[1], "-n") == 0)
		return (ft_echo_n(string, mini));
	ft_putstr_fd(string, mini->stdout);
	free(string);
	return (ft_putchar_fd('\n', mini->stdout));
}
