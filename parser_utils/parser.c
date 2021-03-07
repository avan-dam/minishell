/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 10:25:51 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/07 08:44:43 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_tmps(char *tmp, char *result)
{
	free(tmp);
	if (result)
		free(result);
}

char	*free_reset_tmp(char *tmp, char *result, char *line, int i)
{
	ft_free_tmps(tmp, result);
	return (ft_substr(line, 0, i));
}

static int	free_before_exit(t_base *ptr, t_base *tmp)
{
	int		k;

	k = 0;
	while (ptr)
	{
		if (ptr == tmp)
			k = 1;
		if (k == 1)
			one_baseclear(ptr);
		free(ptr);
		ptr = ptr->next;
	}
	return (-1);
}

static int	send_exec_cmds(t_base *ptr, char **envp, t_mini *mini, char *line)
{
	t_base	*tmp;
	t_base	*tmp2;

	tmp = ptr;
	free(line);
	while (tmp)
	{
		if (exec_cmds(tmp, envp, mini) == -1)
			return (free_before_exit(ptr, tmp));
		tmp2 = tmp->next;
		one_baseclear(tmp);
		tmp = tmp2;
		ft_reset_fds(mini);
	}
	while (ptr)
	{		
		free(ptr);
		ptr = ptr->next;
	}
	return (0);
}

int	parse_input(char *line, t_mini *mini, char **envp, int i)
{
	t_base	*ptr;
	char	*tmp;
	int		k;

	ptr = NULL;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		tmp = ft_strdup(&line[i]);
		k = create_av_list(&ptr, tmp, mini);
		if (k == -1)
		{
			mini->exit = 1;
			return (0);
		}
		i = i + k;
		if (!line[i])
			break ;
		else
			i++;
	}
	return (send_exec_cmds(ptr, envp, mini, line));
}
