/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/17 22:36:40 by salbregh      #+#    #+#                 */
/*   Updated: 2021/04/19 18:59:43 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	main_error_check(int lineret, char *line, t_mini *mini)
{
	if (lineret < 0)
	{
		free(line);
		ft_lstclear(&mini->env1);
		exit(1);
	}
}

static void	ft_send_to_parser(char *line, t_mini *mini, char **envp)
{
	char	*tmp;
	char	*result;

	tmp = line;
	result = check_tokens(tmp, mini, 0, 7);
	if (result != NULL)
	{
		free(result);
		if (parse_input(line, mini, envp, 0) == -1)
			ft_exit(mini, mini->exit);
	}
	else
		free(tmp);
}

void	handle_line(int lineret, t_mini *mini, char **envp)
{
	char	*line;
	char	*templine;
	char	*tmp;

	while (lineret)
	{
		ft_putstr_fd("> ", mini->stdout);
		ft_signals(mini, 0);
		lineret = get_next_line(mini->stdin, &line);
		if (lineret == 0 && ft_strcmp(line, "") == 0)
			ft_signals(mini, 1);
		while (lineret == 0 && line != NULL)
		{
			lineret = get_next_line(mini->stdin, &templine);
			tmp = line;
			line = ft_strjoin(tmp, templine);
			free(templine);
			free(tmp);
		}
		main_error_check(lineret, line, mini);
		ft_send_to_parser(line, mini, envp);
	}
	ft_lstclear(&mini->env1);
}

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;

	if (ac == 1)
	{
		ft_memset(&mini, 0, sizeof(t_mini));
		mini.part = NULL;
		ft_set_env(av, envp, &mini);
		mini.stdout = 1;
		mini.stderr = 2;
		handle_line(1, &mini, envp);
	}
	else
		ft_putstr_fd("No argument needed.\nUsage: ./minishell\n", STDERR);
	return (0);
}
