/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 10:25:51 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/04 11:46:46 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	no_of_commands(char *line, t_mini *mini, int i, int numb)
{
	char	*tmp;
	char	*result;

	tmp = ft_substr(line, 0, i);
	result = check_tokens(tmp, mini, 0, 1);
	while (line[i] && ((line[i] != '|' && line[i] != ';')
			|| (result == NULL)))
	{
		if (line[i] == ' ')
		{
			while (line[i] == ' ')
				i++;
			free(tmp);
			free(result);
			tmp = ft_substr(line, 0, i);
			result = check_tokens(tmp, mini, 0, 1);
			if ((line[i] == '|' || line[i] == ';')
				&& (result != NULL))
			{
				free(tmp);
				free(result);
				mini->numb_cmds = numb;
				mini->cmd_part = ft_substr(line, 0, i);
				if (line[i] == '|')
					mini->type_end = T_PIPE;
				else if (line[i] == ';')
					mini->type_end = T_BREAK;
				return (i);
			}
			numb++;
		}
		if ((line[i] == '>' || line[i] == '<') && line[i + 1] != ' '
			&& line[i + 1] != '"' && line[i + 1] != '\'' && line[i + 1] != '>'
			&& line[i + 1] != '\0')
			numb++;
		i++;
		free(tmp);
		if (result)
			free(result);
		tmp = ft_substr(line, 0, i);
		result = check_tokens(tmp, mini, 0, 1);
	}
	free(tmp);
	mini->numb_cmds = numb;
	free(result);
	mini->cmd_part = ft_substr(line, 0, i);
	mini->type_end = T_END;
	return (i);
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
			return (-1);
		tmp2 = tmp->next;
		one_baseclear(tmp);
		tmp = tmp2;
		// ft_reset_fds(mini);
	}
	while(ptr)
{		free(ptr);
		ptr = ptr->next;}
	// ft_reset_fds(mini);
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
