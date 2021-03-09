/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 14:34:29 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/03/08 20:28:24 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	direction_list(t_base *ptr, int i)
{
	int	j;

	if ((ft_strchr_numb(ptr->av[i + 1], '>', 0) != -1)
		|| (ft_strchr_numb(ptr->av[i + 1], '<', 0) != -1))
	{
		if (ft_strchr_numb(ptr->av[i + 1], '>', 0) != -1)
			j = ft_strchr_numb(ptr->av[i + 1], '>', 0);
		if ((ft_strchr_numb(ptr->av[i + 1], '<', 0) != -1)
			&& ft_strchr_numb(ptr->av[i + 1], '<', 0) < j)
			j = ft_strchr_numb(ptr->av[i + 1], '<', 0);
		if (add_new_into_list(j, ptr, i + 1) == -1)
			i++;
	}
}

static int	open_file_more(t_base *ptr, int i, t_mini *mini)
{
	if (ft_strcmp(">", ptr->av[i]) == 0)
	{
		mini->stdout = open(ptr->av[i + 1], R | C | T, 0666);
		if (mini->stdout == -1)
			return (error_opening(ptr->av[i + 1], mini));
	}
	if (ft_strcmp(">>", ptr->av[i]) == 0)
	{
		mini->stdout = open(ptr->av[i + 1], R | C | A, 0666);
		if (mini->stdout == -1)
			return (error_opening(ptr->av[i + 1], mini));
	}
	if (ft_strcmp("<", ptr->av[i]) == 0)
	{
		mini->stdin = open(ptr->av[i + 1], R, 0666);
		if (mini->stdin == -1)
			return (error_opening(ptr->av[i + 1], mini));
	}
	return (0);
}

static int	ft_open_file(t_base *ptr, int i, t_mini *mini)
{
	if (check_file_toredir(ptr, i, mini) == -1)
		return (-1);
	if (ptr->redir == 0)
		return (i);
	if (open_file_more(ptr, i, mini) == -1)
		return (-1);
	ptr->size = ptr->size - 2;
	ptr->av = ft_remove_redir_av(ptr, i, 0);
	if (ptr->av == NULL)
		return (-1);
	return (i);
}

static char	*ft_change_quote(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		// printf("string[%s] string[i] is %c\n", string, string[i]);
		if (string[i] == '\'' || string[i] == '"')
			ft_memmove(&string[i], &string[i + 1], ft_strlen(string) - i);
		else
			i++;
	}
	return (string);
}

static int	ft_backslash_redir(t_base *ptr, int i, t_mini *mini, int j)
{
	if ((numb_char(ptr->av[i], '"') != 0) || (numb_char(ptr->av[i], '\'') != 0))
	{
		printf("hooo\n");
		// printf("in ptr->av[i][%s]\n", ptr->av[i]);
		ptr->av[i] = ft_change_quote(ptr->av[i]);
		if (ft_check_redir_in_quotes(ptr, mini, i) == 0)
			return (0);
		// printf("in ptr->av[i][%s]\n", ptr->av[i]);
		// return (1);
	}
	printf("hooo\n");
	// if (ft_check_redir_in_quotes(ptr, mini, i) == 0)
	// 	return (0);
	while (ptr->av[i][j] != '>' && ptr->av[i][j] != '<')
		j++;
	if (j <= 0)
	{
		if (ptr->redir == 1)
		{
			direction_list(ptr, i);
			if (ft_open_file(ptr, i, mini) == -1)
				return (-1);
			return (0);
		}
	}
	if (add_new_into_list(j, ptr, i) == -1)
		return (-1);
	return (0);
}

t_base	*ft_redir(t_mini *mini, t_base *ptr)
{
	int		i;

	i = 0;
	// printf("in redir\n");
	while (i < ptr->size && ptr->av[i])
	{
		if ((ft_strchr_numb(ptr->av[i], '>', 0) != -1)
			|| (ft_strchr_numb(ptr->av[i], '<', 0) != -1))
		{
			redir_change_backslash(ptr, i);
			if (ft_backslash_redir(ptr, i, mini, 0) == -1)
				return (NULL);
			// if (ptr->redir == 1 && i != 0)
			// 	i--;
			// if (ptr->redir == 0)
				i++;
		}
		ptr->redir = 0;
		i++;
	}
	return (ptr);
}
