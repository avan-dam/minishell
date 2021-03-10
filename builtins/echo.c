/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:52:44 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/10 20:07:48 by ambervandam   ########   odam.nl         */
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

static char	*ft_avs_into_string(t_base *ptr, int i, char *string2, t_mini *mini)
{
	char	*tmp;
	char	*tmp2;
	char	*string;

	tmp = ft_strdup("");
	tmp2 = ft_strdup("");
	string = NULL;
	while (ptr->av[i])
	{
		string = ft_strjoin(tmp, ptr->av[i]);
		free(tmp);
		// fix check token leaks shiz
		string2 = ft_strjoin(tmp2, check_tokens(ptr->av[i], mini, 0 , 6));
		free(tmp2);
		// printf("ptr->av[i][%s]\n", ptr->av[i]);
		// printf("string2[%s]\n", string2);
		// printf("tmp2[%s]\n", tmp2);
		// printf("string[%s]\n", string);
		// printf("tmp[%s]\n", tmp);
		// if (i + 1 != ptr->size)
		// {
		// 	if (ptr->av[i + 1] && ptr->av[i + 1][0] != '>'
		// 		&& ptr->av[i + 1][0] != '<'
		// 		&& string[ft_strlen(string) - 1] != '\''
		// 		&& string[ft_strlen(string) - 1] != '"'
		// 		&& ft_strcmp("", string) != 0)
		// 	{
		// 		tmp = ft_strdup(string);
		// 		free(string);
		// 		string = ft_strjoin(tmp, " ");
		// 		free(tmp);

		// 		tmp2 = ft_strdup(string2);
		// 		free(string2);
		// 		string2 = ft_strjoin(tmp2, " ");
		// 		free(tmp2);
		// 	}
		// }
		tmp = string;
		tmp2 = string2;
		i++;
	}
	// printf("string is [%s]\n", string);
	free(string);
	i = ft_strlen(string2);
	// printf("string2 is [%s]\n", string2);
	ft_memmove(&string2[i], &string2[i + 1], 1);
	tmp = string2;
	string2 = ft_substr(tmp, 0, ft_strlen(string2) - 1);
	free(tmp);
	// printf("string2 is [%s]\n", string2);
	return (string2);
}

int	ft_echo(t_base *ptr, t_mini *mini)
{
	char	*string;

// divide into ptr->av into echo and -n argv and after
	// printf("in echp\n");
	mini->exit = 0;
	if (ft_strcmp("", ptr->av[0]) == 0)
		return (ft_putstr_fd("", mini->stdout));
	string = ft_avs_into_string(ptr, 1, NULL, mini);
	// printf("string now is [%s]\n", string);
	if (string == NULL || ft_check_empty(string) == 1)
	{
		if (string == NULL)
			free(string);
		return (ft_putchar_fd('\n', mini->stdout));
	}
	// if ((string[0] == '-') && (string[1] == 'n')
	// 	&& ((string[2] == ' ') || (string[2] == '\0') || (string[2] == 'n')))
	if (ft_strcmp(ptr->av[1], "-n") == 0)
		return (ft_echo_n(string, mini));
	ft_putstr_fd(string, mini->stdout);
	free(string);
	return (ft_putchar_fd('\n', mini->stdout));
}
