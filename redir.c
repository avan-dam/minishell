/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 14:34:29 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/02/02 14:45:26 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// CLEAN UP THIS FILE
// WRITE PARSER SO IT WORKS WITH REDIR
// SO LOOK AT ALL > < and BACKSLASH

static int	ft_remove_redir_argv(t_base *ptr, int i, int j)
{
	char	**temp;

	ptr->size = ptr->size - 2;
	if ((temp = (char **)malloc(sizeof(char *) * (ptr->size + 1))) == NULL)
		return (-1);
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
	while (j < ptr->size + 2)
	{
		free(ptr->argv[j]);
		ptr->argv[j] = NULL;
		j++;
	}
	ptr->argv = temp;
	return (0);
}

static int		error_opening(char *error, t_mini *mini)
{
	ft_putstr_fd("bash: ", mini->stderr);
	ft_putstr_fd(error, mini->stderr);
	ft_putstr_fd(": No such file or directory\n", mini->stderr);
	ft_reset_fds(mini);
	mini->exit = 1;
	return (-1);
}

static int		ft_open_file(t_base *ptr, int i, t_mini *mini)
{
	if (ptr->redir == 0)
		return (i);
	if (ft_strcmp(">", ptr->argv[i]) == 0)
	{
		if ((mini->stdout = open(ptr->argv[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
			return (error_opening(ptr->argv[i + 1], mini));
	}
	if (ft_strcmp(">>", ptr->argv[i]) == 0)
	{
		if ((mini->stdout = open(ptr->argv[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666)) == -1)
			return (error_opening(ptr->argv[i + 1], mini));
	}
	if (ft_strcmp("<", ptr->argv[i]) == 0)
	{
		if ((mini->stdin = open(ptr->argv[i + 1], O_RDWR, 0666)) == -1)
			return (error_opening(ptr->argv[i + 1], mini));
	}
	if (ft_remove_redir_argv(ptr, i, 0) == -1)
		return (-1);
	return (i);
}

static char		**add_tmp_tolist(char *tmp, t_base *ptr, int i, int j)
{
	char	**new;

	if ((new = (char **)malloc(sizeof(char *) * (ptr->size + 1))) == NULL)
		return (NULL);
	while (j < i)
	{
		new[j] = ft_strdup(ptr->argv[j]);
		j++;
	}
	new[j] = ft_strdup(tmp);
	j++;
	while (j < ptr->size)
	{
		new[j] = ft_strdup(ptr->argv[j - 1]);
		j++;
	}
	new[j] = NULL;
	j = 0;
	while (j < ptr->size - 1)
	{
		free(ptr->argv[j]);
		ptr->argv[j] = NULL;
		j++;
	}
	return (new);
}

static char		*add_new_backslash_into_list(int j, t_base *ptr, int i)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (j + 1));
	if (tmp == NULL)
		return (NULL);
	tmp[j] = '\0';
	j--;
	while (j >= 0)
	{
		tmp[j] = '\\';
		j--;
	}
	if (ptr->redir == 1)
		tmp = ft_strjoin(tmp, "\\");
	if (i > 0)
	{
		ptr->size = ptr->size + 1;
		if ((ptr->argv = add_tmp_tolist(tmp, ptr, i, 0)) == NULL)
			return (NULL);
	}
	return (tmp);
}

static void	remove_extra_backslash_check_redir(t_base *ptr, int i)
{
	int j;

	j = 0;
	while (ptr->argv[i][j] == '\\')
		j++;
	if (j % 2 == 0)
		ptr->redir = 1;
	j = 0;
	while (ptr->argv[i][j] == '\\')
	{
		if (ptr->argv[i][j + 1] == '\\')
			ft_memmove(&ptr->argv[i][j], &ptr->argv[i][j + 1], ft_strlen(ptr->argv[i]) - j);
		j++;
	}
}

static int	ft_backslash_redir(t_base *ptr, int i, t_mini *mini)
{
	int		j;
	char	*tmp;

	tmp = NULL;
	j = 0;
	remove_extra_backslash_check_redir(ptr, i);
	while (ptr->argv[i][j] == '\\')
		j++;
	if (j <= 0)
	{
		if (ptr->redir == 1)
		{
			if (ft_open_file(ptr, i, mini) == -1)
				return (-1);
			return (i);
		}
	}
	if (j > 0)
		ptr->argv[i] = ft_substr(ptr->argv[i], j, ft_strlen(ptr->argv[i]) - j);
	if ((tmp = add_new_backslash_into_list(j - 1, ptr, i)) == NULL)
		return (-1);
	return (i);
}

t_base		*ft_redir(t_mini *mini, t_base *ptr)
{
	int		i;

	i = 0;
	ptr->redir = 0;
	while (i < ptr->size - 1)
	{
		if ((ft_strchr_numb(ptr->argv[i], '>', 0) != -1) || (ft_strchr_numb(ptr->argv[i], '<', 0) != -1))
		{
			if (ft_backslash_redir(ptr, i, mini) == -1)
				return (NULL);
			if (ptr->redir == 1)
				i--;
			if (ptr->redir == 0)
				i++;
		}
		ptr->redir = 0;
		i++;
	}
	return (ptr);
}
