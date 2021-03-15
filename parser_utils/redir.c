/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 14:34:29 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/03/15 14:53:44 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	direction_list(t_base *ptr, int i, t_mini *mini)
{
	int		j;
	int		k;
	char	*temp;

	k = 0;
	while (ptr->av[i][k + 1])
	{
		if ((ptr->av[i][k] == '<' && ptr->av[i][k + 1] == '<')
			|| (ptr->av[i][k] == '<' && ptr->av[i][k + 1] == '>')
			|| (ptr->av[i][k] == '>' && ptr->av[i][k + 1] == '<'))
		{
			ft_putstr_fd("bash: syntax error near ", mini->stderr);
			ft_putstr_fd("unexpected token `", mini->stderr);
			ft_putchar_fd(ptr->av[i][k + 1], mini->stderr);
			ft_putstr_fd("'\n", mini->stderr);
			mini->exit = 258;
			return (-1);
		}
		k++;
	}
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
	i = 0;
	while (ptr->av[i])
	{
		temp = ptr->av[i];
		ptr->av[i] = ft_strtrim_backslash(temp, ' ');
		free(temp);
		i++;
	}
	return (0);
}

static int	open_file_more(t_base *ptr, int i, t_mini *mini)
{
	char	*opendir;
	char	*filename;
	int		ret;

	opendir = ptr->av[i];
	filename = ptr->av[i + 1];
	ret = 0;
	if ((ptr->av[i + 2]) && (ft_strcmp(ptr->av[i + 1], "") == 0)
		&& (ft_strcmp(ptr->av[i + 2], "") != 0))
	{
		filename = ptr->av[i + 2];
		ret = 1;
	}
	if (ft_strcmp(">", opendir) == 0)
	{
		mini->stdout = open(filename, R | C | T, 0666);
		if (mini->stdout == -1)
			return (error_opening(filename, mini));
	}
	if (ft_strcmp(">>", opendir) == 0)
	{
		mini->stdout = open(filename, R | C | A, 0666);
		if (mini->stdout == -1)
			return (error_opening(filename, mini));
	}
	if (ft_strcmp("<", opendir) == 0)
	{
		mini->stdin = open(filename, R, 0666);
		if (mini->stdin == -1)
			return (error_opening(filename, mini));
	}
	return (ret);
}

static int	ft_open_file(t_base *ptr, int i, t_mini *mini)
{
	int	ret;

	// printf("here\n");
	if (check_file_toredir(ptr, i, mini) == -1)
		return (-1);
	if (ptr->redir == 0)
		return (i);
	ret = open_file_more(ptr, i, mini);
	if (ret == -1)
		return (-1);
	ptr->size = ptr->size - 2;
	if (ret == 0)
		ptr->av = ft_remove_redir_av(ptr, i, 0);
	if (ret == 1)
		ptr->av = ft_remove_redir_av(ptr, i + 1, 0);
	if (ptr->av == NULL)
		return (-1);
	return (i);
}

static int	ft_backslash_redir(t_base *ptr, int i, t_mini *mini, int j)
{
	if ((numb_char(ptr->av[i], '"') != 0) || (numb_char(ptr->av[i], '\'') != 0))
	{
		ptr->av[i] = mem_check_tkns(ptr->av[i], mini, 0, 4);
		ptr->redir = 5;
		return (1);
	}
	if (ft_check_redir_in_quotes(ptr, mini, i) == 0)
		return (0);
	while (ptr->av[i][j] != '>' && ptr->av[i][j] != '<')
		j++;
	if (j <= 0)
	{
		if (ptr->redir == 1)
		{
			if (direction_list(ptr, i, mini) == -1)
				return (-1);
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
	while (ptr->av[i] && i < ptr->size)
	{
		if ((ft_strchr_numb(ptr->av[i], '>', 0) != -1)
			|| (ft_strchr_numb(ptr->av[i], '<', 0) != -1))
		{
			redir_change_backslash(ptr, i);
			if (ft_backslash_redir(ptr, i, mini, 0) == -1)
				return (NULL);
			if (ptr->redir == 1 && i != 0)
				i--;
			if (ptr->redir == 0 || ptr->redir == 5)
				i++;
		}
		ptr->redir = 0;
		i++;
	}
	return (ptr);
}
