/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:52:44 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/26 10:33:41 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_n_argv(char *str, t_mini *mini)
{
	int		i;
	char	*tempptr;

	i = 0;
	if (str == NULL || ft_strcmp(str, "") == 0 || ft_strcmp(str, "-") == 0)
		return (free_return(str));
	tempptr = str;
	str = ft_strtrim_backslash(tempptr, ' ');
	free(str);
	str = check_tokens(str, mini, 0, 6);
	if (str == NULL || ft_strcmp(str, "") == 0 || ft_strcmp(str, "-") == 0)
		return (free_return(str));
	if (str[i] != '-')
		return (free_return(str));
	i++;
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (free_return(str));
	free(str);
	return (1);
}

static char	*trim_string(t_base *ptr, char *str, int i)
{
	int	k;

	if (!(ptr->av[i + 1]) && str && str[ft_strlen(str) - 1] == ' ')
	{
		k = ft_strlen(str) - 1;
		while (k >= 0)
		{
			if (str[k] == ' ')
				ft_memmove(&str[k], &str[k + 1], ft_strlen(str) - k);
			k--;
		}
	}
	return (str);
}

static char	*set_string_after_n(t_base *ptr, int i, t_mini *mini, char *tmp)
{
	char	*tmp2;
	char	*str;

	str = NULL;
	while (ptr->av[i])
	{
		if (!(ptr->av[i + 1]))
			check_last_arg(ptr, i);
		tmp2 = check_tokens(ptr->av[i], mini, 0, 6);
		if ((check_empty(tmp2) == -1) && (numb_char(ptr->av[i], '$') > 0))
		{
			free(tmp2);
			tmp2 = ft_strdup("");
			str = trim_string(ptr, str, i);
		}
		if (!(ptr->av[i + 1]) && (numb_char(ptr->av[i], '\\') > 0) && i == 1)
			tmp2 = trim_string(ptr, tmp2, i);
		str = ft_strjoin(tmp, tmp2);
		free(tmp2);
		free(tmp);
		tmp = str;
		i++;
	}
	return (str);
}

static char	*ft_avs_into_str(t_base *ptr, int i, t_mini *mini)
{
	char	*tempptr;
	char	*str;

	tempptr = ptr->av[i];
	while (check_n_argv(tempptr, mini) == 1)
	{
		free(ptr->av[i]);
		ptr->av[i] = ft_strdup("-n");
		i++;
		if (ptr->av[i] == NULL)
			break ;
		tempptr = ptr->av[i];
	}
	str = set_string_after_n(ptr, i, mini, NULL);
	return (str);
}

int	ft_echo(t_base *ptr, t_mini *mini)
{
	char	*str;

	if ((ft_strcmp("", ptr->av[0]) == 0) || (ptr->av[1] == NULL))
	{
		mini->exit = 0;
		return (ft_putstr_fd("", mini->stdout));
	}
	str = ft_avs_into_str(ptr, 1, mini);
	mini->exit = 0;
	if (ft_strcmp(ptr->av[1], "-n") == 0)
		return (ft_echo_n(str, mini));
	if (str == NULL || ft_check_empty(str) == 1)
	{
		if (str == NULL || ft_strcmp("", str) == 0)
			free(str);
		return (ft_putchar_fd('\n', mini->stdout));
	}
	ft_putstr_fd(str, mini->stdout);
	free(str);
	return (ft_putchar_fd('\n', mini->stdout));
}
