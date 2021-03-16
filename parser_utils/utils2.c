/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 19:28:33 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/03/16 14:27:15 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_str_int(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strtolower(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 65 && str[i] <= 90)
			str[i] = str[i] + 32;
		i++;
	}
	return (str);
}

char	*ft_trim_paths(char *line, char *set)
{
	char	*tmp1;
	int		i;
	char	*tmp2;

	tmp2 = NULL;
	i = 0;
	tmp1 = ft_strtrim(line, set);
	if (tmp1[0] == ' ' || tmp1[ft_strlen(tmp1)] == ' ')
	{
		tmp2 = ft_strtrim(tmp1, " ");
		free(tmp1);
		return (tmp2);
	}
	return (tmp1);
}

char	*mem_check_tkns(char *str, t_mini *mini, int i, int j)
{
	char	*temp;

	temp = str;
	str = check_tokens(temp, mini, i, j);
	free(temp);
	return (str);
}

int	unvalid_ident(char *error, t_mini *mini, int exitstatus)
{
	if ((ft_strcmp(error, "|") == 0)
		|| (ft_strcmp(error, ";") == 0))
	{
		ft_putstr_fd("bash: syntax error ", mini->stderr);
		ft_putstr_fd("near unexpected token '", mini->stderr);
		ft_putstr_fd(error, mini->stderr);
		ft_putstr_fd("'\n", mini->stderr);
		mini->exit = exitstatus;
		return (-1);
	}
	if (ft_strcmp(error, "\\$?") == 0)
		error = "$?";
	ft_putstr_fd("bash: ", mini->stderr);
	ft_putstr_fd(error, mini->stderr);
	ft_putstr_fd(": command not found\n", mini->stderr);
	mini->exit = exitstatus;
	return (-1);
}

int	ft_check_empty(char *string)
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
