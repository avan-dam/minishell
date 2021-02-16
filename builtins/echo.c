/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:52:44 by salbregh      #+#    #+#                 */
/*   Updated: 2021/02/16 16:16:30 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_howmany_n(char *string, int i, int j)
{
	// char *temp;??
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
	string = ft_strtrim(tmp, " ");
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

static char	*ft_argvs_into_string(t_base *ptr, int i, char *string)
{
	char	*tmp;

	tmp = ft_strdup("");
	while (ptr->argv[i])
	{
		if (string)
			free(string);
		string = ft_strjoin(tmp, ptr->argv[i]);
		free(tmp);
		if (i + 1 != ptr->size)
		{
			if (ptr->argv[i + 1] && ptr->argv[i + 1][0] != '>'
			&& ptr->argv[i + 1][0] != '<')
			{
				tmp = ft_strdup(string);
				free(string);
				string = ft_strjoin(tmp, " ");
			}
		}
		tmp = string;
		i++;
	}
	return (string);
}

int			ft_echo(t_base *ptr, t_mini *mini)
{
	char	*string;
	char	*tmp;

	mini->exit = 0;
			// 	printf("before\n");
			// ft_leaks();
	if (ft_strcmp("", ptr->argv[0]) == 0)
		return (ft_putstr_fd("", mini->stdout));
	string = ft_argvs_into_string(ptr, 1, NULL);
	if (string == NULL || ft_check_empty(string) == 1)
	{
		// if (string)
			// free(string);// this breaks when echo $POEP $MEERPOEP
		string = NULL;
		return (ft_putchar_fd('\n', mini->stdout));
	}
	if ((string[0] == '-') && (string[1] == 'n') &&
	((string[2] == ' ') || (string[2] == '\0') || (string[2] == 'n')))
	{
		if (ft_echo_n(string, mini) != 2)
		{
			// printf("after\n");
			// ft_leaks();
			return (0);
		}
	}
	tmp = string;
	string = ft_strtrim(tmp, " ");
	ft_putstr_fd(string, mini->stdout);
	free(string);
	// printf("after\n");
	// ft_leaks();
	return (ft_putchar_fd('\n', mini->stdout));
}
