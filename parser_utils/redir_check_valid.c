/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_check_valid.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 09:44:30 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/03/24 14:15:21 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_change_backslash(t_base *ptr, int i)
{
	int		j;

	j = 0;
	while (ptr->av[i][j] == '\\')
		j++;
	if (j % 2 == 0)
		ptr->redir = 1;
	j = 0;
	while (ptr->av[i][j] == '\\')
	{
		if (ptr->av[i][j + 1] == '\\')
		{
			ft_memmove(&ptr->av[i][j], &ptr->av[i][j + 1],
				ft_strlen(ptr->av[i]) - j);
		}
		j++;
	}
}

static char	*ft_avs_before_redir(t_base *ptr, int max, int i, char *str)
{
	char	*tmp;

	tmp = ft_strdup("");
	while (i != max && ptr->av[i])
	{
		if (str)
			free(str);
		str = ft_strjoin(tmp, ptr->av[i]);
		free(tmp);
		if (i + 1 != max)
		{
			if (ptr->av[i + 1] && ptr->av[i + 1][0] != '>'
				&& ptr->av[i + 1][0] != '<')
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

int	ft_check_redir_in_quotes(t_base *ptr, t_mini *mini, int i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_avs_before_redir(ptr, i, 0, NULL);
	tmp2 = check_tokens(tmp, mini, 0, 1);
	if ((tmp != NULL && tmp2 == NULL) || (numb_char(ptr->av[i], '\'') > 0
			|| (numb_char(ptr->av[i], '"') > 0)))
	{
		ptr->av[i] = mem_check_tkns(ptr->av[i], mini, 0, 2);
		ptr->redir = 3;
		free(tmp);
		free(tmp2);
		return (0);
	}
	free(tmp);
	free(tmp2);
	return (1);
}

int	check_file_toredir(t_base *ptr, int i, t_mini *mini)
{
	char	*tmp;

	if (ptr->av[i + 1] == NULL)
		return (redir_error(mini, 1));
	tmp = ptr->av[i + 1];
	ptr->av[i + 1] = check_tokens(tmp, mini, 0, 0);
	free(tmp);
	if (ptr->av[i + 1] == NULL)
		return (-1);
	if (ft_strcmp(ptr->av[i + 1], ">") == 0)
		return (redir_error(mini, 1));
	return (0);
}

int	direction_list(t_base *ptr, int i, int j, int k)
{
	char	*temp;

	if ((ft_strchr_numb(ptr->av[i + 1], '>', 0) != -1)
		|| (ft_strchr_numb(ptr->av[i + 1], '<', 0) != -1))
	{
		if (ft_strchr_numb(ptr->av[i + 1], '>', 0) != -1)
			j = ft_strchr_numb(ptr->av[i + 1], '>', 0);
		if ((ft_strchr_numb(ptr->av[i + 1], '<', 0) != -1)
			&& ft_strchr_numb(ptr->av[i + 1], '<', 0) < j)
			j = ft_strchr_numb(ptr->av[i + 1], '<', 0);
		if (add_new_into_list(j, ptr, i + 1) == -1)
			i++;
	}
	while (ptr->av[k])
	{
		if (ft_strcmp(ptr->av[0], "echo") != 0 || numb_char(ptr->av[k], '>') > 0
			|| numb_char(ptr->av[k], '<') > 0)
		{
			temp = ptr->av[k];
			ptr->av[k] = ft_strtrim_backslash(temp, ' ');
			free(temp);
		}
		k++;
	}
	return (0);
}
