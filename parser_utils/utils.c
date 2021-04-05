/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 17:39:30 by salbregh      #+#    #+#                 */
/*   Updated: 2021/04/05 13:29:09 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr_numb(char *line, char c, int i)
{
	if (line == NULL || i < 0)
		return (-1);
	while (line[i] != '\0')
	{
		if (line[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	numb_char(char *line, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (line == NULL)
		return (0);
	while (line[i] != '\0')
	{
		if (line[i] == c)
			j++;
		i++;
	}
	return (j);
}

char	*ft_strjoin_three(char *start, char *newvar, char *end)
{
	char	*temp;
	char	*newline;

	temp = ft_strjoin(start, newvar);
	newline = ft_strjoin(temp, end);
	free(start);
	free(newvar);
	free(end);
	free(temp);
	return (newline);
}

char	*ft_string_insert(char *string, int i, char *middle)
{
	char	*start;
	char	*end;

	start = ft_substr(string, 0, i + 1);
	end = ft_substr(string, i + 1, ft_strlen(string) - i - 1);
	return (ft_strjoin_three(start, middle, end));
}

int	error_opening(char *error, t_mini *mini)
{
	ft_putstr_fd("bash: ", mini->stderr);
	ft_putstr_fd(error, mini->stderr);
	ft_putstr_fd(": No such file or directory\n", mini->stderr);
	ft_reset_fds(mini);
	mini->exit = 1;
	return (-1);
}
