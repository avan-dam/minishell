/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 16:52:44 by salbregh      #+#    #+#                 */
/*   Updated: 2021/03/22 15:04:17 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_howmany_n(char *str, int i, int j)
{
	if (ft_strcmp(str, "-n") == 0)
		return (ft_substr(str, 3, ft_strlen(str) - 3));
	while (str[i] != '\0')
	{
		j = i;
		if (str[i] != '-')
			return (ft_substr(str, j, ft_strlen(str) - j));
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] != ' ')
			return (ft_substr(str, j, ft_strlen(str) - j));
		i++;
	}
	return ("");
}

static int	ft_echo_n(char *str, t_mini *mini)
{
	if (str == NULL)
		return (0);
	str = ft_howmany_n(str, 0, 0);
	if (ft_strcmp(str, "") == 0)
		return (0);
	ft_putstr_fd(str, mini->stdout);
	free(str);
	return (0);
}

static int	free_return(char *str)
{
	free(str);
	return (-1);
}

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

static int	check_empty(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || ft_strcmp(str, "") == 0)
		return (-1);
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (-1);
}

static char	*try_this(t_base *ptr, char *str, int i)
{
	int k;
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

static char	*ft_avs_into_str(t_base *ptr, int i, char *str, t_mini *mini)
{
	char	*tmp2;
	char	*tempptr;
	char	*tmp22;
	// int		k;

	tmp2 = NULL;
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
	while (ptr->av[i])
	{
		if (!(ptr->av[i + 1]))
		{
			tempptr = ptr->av[i];
			if (ft_strcmp(ptr->av[i], "") != 0)
				free(ptr->av[i]);
			ptr->av[i] = ft_strtrim_backslash(tempptr, ' ');
		}
		tmp22 = check_tokens(ptr->av[i], mini, 0, 6);
		if ((check_empty(tmp22) == -1) && (numb_char(ptr->av[i], '$') > 0))
		{
			free(tmp22);
			tmp22 = ft_strdup("");
			str = try_this(ptr, str, i);
			// if (!(ptr->av[i + 1]) && str && str[ft_strlen(str) - 1] == ' ')
			// {
			// 	k = ft_strlen(str) - 1;
			// 	while (k >= 0)
			// 	{
			// 		if (str[k] == ' ')
			// 			ft_memmove(&str[k], &str[k + 1], ft_strlen(str) - k);
			// 		k--;
			// 	}
			// }
		}
		if (!(ptr->av[i + 1]) && (numb_char(ptr->av[i], '\\') > 0) && i == 1)
		{
			tmp22 = try_this(ptr, tmp22, i);
			// if (!(ptr->av[i + 1]) && tmp22 && tmp22[ft_strlen(tmp22) - 1] == ' ')
			// {
			// 	k = ft_strlen(tmp22) - 1;
			// 	while (k >= 0)
			// 	{
			// 		if (tmp22[k] == ' ')
			// 			ft_memmove(&tmp22[k], &tmp22[k + 1], ft_strlen(tmp22) - k);
			// 		k--;
			// 	}
			// }
		}
		str = ft_strjoin(tmp2, tmp22);
		free(tmp22);
		free(tmp2);
		tmp2 = str;
		i++;
	}
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
	str = ft_avs_into_str(ptr, 1, NULL, mini);
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
