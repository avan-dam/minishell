/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 10:25:51 by salbregh      #+#    #+#                 */
/*   Updated: 2021/04/13 20:12:34 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	free_before_exit(t_base *ptr, t_base *tmp)
{
	int		k;
	t_base	*tmp2;

	k = 0;
	while (ptr)
	{
		if (ptr == tmp)
			k = 1;
		if (k == 1)
			one_baseclear(ptr);
		tmp2 = ptr->next;
		free(ptr);
		ptr = tmp2;
	}
	return (-1);
}

static int	check_valid_dividers(t_base *t, t_base *t2, t_base *t3, t_mini *m)
{
	while (t)
	{
		if ((t->av[0][0] == ';')
			|| (t->av[0][0] == '|'))
		{
			ft_putstr_fd("bash: syntax error near ", m->stderr);
			ft_putstr_fd("unexpected token `", m->stderr);
			ft_putchar_fd(t->av[0][0], m->stderr);
			ft_putstr_fd("'\n", m->stderr);
			m->exit = 258;
			while (t2)
			{
				one_baseclear(t2);
				t2 = t2->next;
			}
			while (t3)
			{		
				free(t3);
				t3 = t3->next;
			}
			return (-1);
		}
		t = t->next;
	}
	return (0);
}

static int	send_exec_cmds(t_base *ptr, char **envp, t_mini *mini, char *line)
{
	t_base	*tmp;
	t_base	*tmp2;

	tmp = ptr;
	if (line)
		free(line);
	if (check_valid_dividers(ptr, ptr, ptr, mini) == -1)
		return (0);
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
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
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
