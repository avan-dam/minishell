/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_check_valid.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 09:44:30 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/02/17 09:47:58 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		redir_change_backslash(t_base *ptr, int i)
{
	int		j;

	j = 0;
	while (ptr->argv[i][j] == '\\')
		j++;
	if (j % 2 == 0)
		ptr->redir = 1;
	j = 0;
	while (ptr->argv[i][j] == '\\')
	{
		if (ptr->argv[i][j + 1] == '\\')
		{
			ft_memmove(&ptr->argv[i][j], &ptr->argv[i][j + 1],
			ft_strlen(ptr->argv[i]) - j);
		}
		j++;
	}
}

static char	*ft_argvs_before_redir(t_base *ptr, int max, int i, char *str)
{
	char	*tmp;

	tmp = ft_strdup("");
	while (i != max && ptr->argv[i])
	{
		if (str)
			free(str);
		str = ft_strjoin(tmp, ptr->argv[i]);
		free(tmp);
		if (i + 1 != max)
		{
			if (ptr->argv[i + 1] && ptr->argv[i + 1][0] != '>'
			&& ptr->argv[i + 1][0] != '<')
			{
				tmp = ft_strdup(str);
				free(str);
				str = ft_strjoin(tmp, " ");
				free(tmp);
			}
		}
		tmp = ft_strdup(str);
		i++;
	}
	free(tmp);
	return (str);
}

int			ft_check_redir_in_quotes(t_base *ptr, t_mini *mini, int i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_argvs_before_redir(ptr, i, 0, NULL);
	tmp2 = check_tokens(tmp, mini, 0, 1);
	if ((tmp != NULL && tmp2 == NULL) ||
	(numb_char(ptr->argv[i], '\'') > 0 || numb_char(ptr->argv[i], '"') > 0))
	{
		ptr->argv[i] = memory_check_tokens(ptr->argv[i], mini, 0, 2);
		ptr->redir = 3;
		free(tmp);
		free(tmp2);
		return (0);
	}
	free(tmp);
	free(tmp2);
	return (1);
}

int			check_file_toredir(t_base *ptr, int i, t_mini *mini)
{
	char *tmp;

	tmp = ptr->argv[i + 1];
	ptr->argv[i + 1] = check_tokens(tmp, mini, 0, 0);
	free(tmp);
	if (ptr->argv[i + 1] == NULL || ft_strcmp(ptr->argv[i + 1], ">") == 0)
	{
		ft_putstr_fd("bash: syntax error near ", mini->stderr);
		ft_putstr_fd("unexpected token `newline'\n", mini->stderr);
		ft_reset_fds(mini);
		mini->exit = 258;
		return (-1);
	}
	return (0);
}