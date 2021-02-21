/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 19:28:33 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/02/21 19:59:09 by ambervandam   ########   odam.nl         */
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

char	*memory_check_tokens(char *str, t_mini *mini, int i, int j)
{
	char	*temp;

	temp = str;
	str = check_tokens(temp, mini, i, j);
	free(temp);
	return (str);
}

int	unvalid_ident(char *error, t_mini *mini, int exitstatus)
{
	if (ft_strcmp(error, "\\$?") == 0)
		error = "$?";
	ft_putstr_fd("bash: ", mini->stderr);
	ft_putstr_fd(error, mini->stderr);
	ft_putstr_fd(": command not found\n", mini->stderr);
	mini->exit = exitstatus;
	return (-1);
}