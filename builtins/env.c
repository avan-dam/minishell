/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 22:27:08 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/29 11:30:59 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	up_shell_level(t_mini *mini)
{
	char	*tmp;

	ft_unset(mini, "SHLVL");
	mini->shell_level++;
	tmp = ft_itoa(mini->shell_level);
	ft_add_env("SHLVL", tmp, mini);
	free(tmp);
}

static int	ft_set_shell_level(char *str, t_mini *mini)
{
	char	*tmp;
	int		i;
	int		level;

	if (mini->shell_level != 0)
		return (mini->shell_level);
	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	tmp = str;
	str = ft_substr(tmp, i, ft_strlen(str));
	level = ft_atoi(str);
	free(str);
	return (level);
}

void	ft_set_env(char **av, char **envp, t_mini *mini)
{
	int		i;

	i = 0;
	(void)av;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "OLDPWD", 6) == 0)
		{
			i++;
			continue ;
		}
		else if (ft_strncmp(envp[i], "SHLVL", 5) == 0)
		{
			mini->shell_level = ft_set_shell_level(envp[i], mini);
			i++;
			continue ;
		}
		ft_split_into_tlist(mini, envp[i]);
		i++;
	}
	envp[i] = NULL;
	up_shell_level(mini);
	mini->exit = 0;
}

static void	ft_env_error(t_mini *mini, t_base *ptr)
{
	ft_putstr_fd("env: ", STDOUT);
	ft_putstr_fd(ptr->av[1], STDOUT);
	ft_putstr_fd(": No such file or directory\n", STDOUT);
	mini->exit = 127;
}

void	ft_lstprint_env(t_list *lst, t_mini *mini, t_base *ptr)
{
	t_list	*tmp;

	tmp = lst;
	if (tmp == NULL)
		return ;
	if (ptr->av[1])
	{
		ft_env_error(mini, ptr);
		return ;
	}
	while (tmp != NULL)
	{
		if (tmp->var2 == NULL)
		{
			tmp = tmp->next;
			continue ;
		}
		ft_putstr_fd(tmp->var1, mini->stdout);
		ft_putstr_fd("=", mini->stdout);
		ft_putstr_fd(tmp->var2, mini->stdout);
		ft_putstr_fd("\n", mini->stdout);
		tmp = tmp->next;
	}
}
