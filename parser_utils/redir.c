/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 14:34:29 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/02/16 14:28:59 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**add_tmp_tolist(char *tmp, t_base *ptr, int i, int j)
{
	char	**new;

	if ((new = (char **)malloc(sizeof(char *) * (ptr->size + 1))) == NULL)
		return (NULL);
	while (j < i)
	{
		new[j] = ft_strdup(ptr->argv[j]);
		j++;
	}
	new[j] = tmp;
	j++;
	while (j < ptr->size)
	{
		new[j] = ft_strdup(ptr->argv[j - 1]);
		j++;
	}
	new[j] = NULL;
	j = 0;
	while (ptr->argv[j])
	{
		free(ptr->argv[j]);
		ptr->argv[j] = NULL;
		j++;
	}
	free(ptr->argv);
	return (new);
}

static int	add_new_into_list(int j, t_base *ptr, int i)
{
	char	*tmp;
	char	*newargv;

	tmp = NULL;
	if (j > 0)
	{
		tmp = ft_substr(ptr->argv[i], 0, j);
		if (ptr->redir != 1 && numb_char(tmp, '\\') == (int)ft_strlen(tmp))
			tmp = ft_memmove(&tmp[0], &tmp[1], ft_strlen(tmp));
		newargv = ptr->argv[i];
		ptr->argv[i] = ft_substr(newargv, j, ft_strlen(newargv) - j);
		free(newargv);
	}
	if (i > 0)
	{
		ptr->size = ptr->size + 1;
		if ((ptr->argv = add_tmp_tolist(tmp, ptr, i, 0)) == NULL)
			return (-1);
	}
	return (0);
}

static char	**ft_remove_redir_argv(t_base *ptr, int i, int j)
{
	char	**temp;

	ptr->size = ptr->size - 2;
	if ((temp = (char **)malloc(sizeof(char *) * (ptr->size + 1))) == NULL)
		return (NULL);
	while (j < i)
	{
		temp[j] = ft_strdup(ptr->argv[j]);
		j++;
	}
	while (j < ptr->size)
	{
		temp[j] = ft_strdup(ptr->argv[j + 2]);
		j++;
	}
	temp[j] = NULL;
	j = 0;
	while (ptr->argv[j])
	{
		free(ptr->argv[j]);
		ptr->argv[j] = NULL;
		j++;
	}
	free(ptr->argv);
	return (temp);
}

static int	error_opening(char *error, t_mini *mini)
{
	ft_putstr_fd("bash: ", mini->stderr);
	ft_putstr_fd(error, mini->stderr);
	ft_putstr_fd(": No such file or directory\n", mini->stderr);
	ft_reset_fds(mini);
	mini->exit = 1;
	return (-1);
}

static void	direction_list(t_base *ptr, int i)
{
	int j;

	if ((ft_strchr_numb(ptr->argv[i + 1], '>', 0) != -1) ||
		(ft_strchr_numb(ptr->argv[i + 1], '<', 0) != -1))
	{
		if (ft_strchr_numb(ptr->argv[i + 1], '>', 0) != -1)
			j = ft_strchr_numb(ptr->argv[i + 1], '>', 0);
		if ((ft_strchr_numb(ptr->argv[i + 1], '<', 0) != -1) &&
		ft_strchr_numb(ptr->argv[i + 1], '<', 0) < j)
			j = ft_strchr_numb(ptr->argv[i + 1], '<', 0);
		if (add_new_into_list(j, ptr, i + 1) == -1)
			i++;
	}
}

static int	check_file_toredir(t_base *ptr, int i, t_mini *mini)
{
	char *tmp;
	tmp = ptr->argv[i + 1];
	ptr->argv[i + 1] = check_tokens(tmp, mini, 0, 0);
	free(tmp);
	if (ptr->argv[i + 1] == NULL || ft_strcmp(ptr->argv[i + 1], ">") == 0)
	{
		printf("in hereeee\n");
		ft_putstr_fd("bash: syntax error near ", mini->stderr);
		ft_putstr_fd("unexpected token `newline'\n", mini->stderr);
		ft_reset_fds(mini);
		mini->exit = 258;
		// MEM LEAK IN THIS
		return (-1);
	}
	return (0);
}

static int	ft_open_file(t_base *ptr, int i, t_mini *mini)
{
	if (check_file_toredir(ptr, i, mini) == -1)
		return (-1);
	if (ptr->redir == 0)
		return (i);
	if (ft_strcmp(">", ptr->argv[i]) == 0)
	{
		if ((mini->stdout = open(ptr->argv[i + 1], R | C | T, 0666)) == -1)
			return (error_opening(ptr->argv[i + 1], mini));
	}
	if (ft_strcmp(">>", ptr->argv[i]) == 0)
	{
		if ((mini->stdout = open(ptr->argv[i + 1], R | C | A, 0666)) == -1)
			return (error_opening(ptr->argv[i + 1], mini));
	}
	if (ft_strcmp("<", ptr->argv[i]) == 0)
	{
		if ((mini->stdin = open(ptr->argv[i + 1], R, 0666)) == -1)
			return (error_opening(ptr->argv[i + 1], mini));
	}
	if ((ptr->argv = ft_remove_redir_argv(ptr, i, 0)) == NULL)
		return (-1);
	return (i);
}

static void	check_extra_backslash(t_base *ptr, int i)
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

static int	ft_backslash_redir(t_base *ptr, int i, t_mini *mini, int j)
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
	while (ptr->argv[i][j] != '>' && ptr->argv[i][j] != '<')
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

t_base		*ft_redir(t_mini *mini, t_base *ptr)
{
	int		i;

	i = 0;
	while (i < ptr->size && ptr->argv[i])
	{
		if ((ft_strchr_numb(ptr->argv[i], '>', 0) != -1) ||
		(ft_strchr_numb(ptr->argv[i], '<', 0) != -1))
		{
			check_extra_backslash(ptr, i);
			if (ft_backslash_redir(ptr, i, mini, 0) == -1)
				return (NULL);
			if (ptr->redir == 1 && i != 0)
				i--;
			if (ptr->redir == 0)
				i++;
		}
		ptr->redir = 0;
		i++;
	}
	return (ptr);
}
