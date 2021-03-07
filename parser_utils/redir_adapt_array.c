/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_adapt_array.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 09:38:57 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/02/23 18:28:46 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_opening(char *error, t_mini *mini)
{
	ft_putstr_fd("bash: ", mini->stderr);
	ft_putstr_fd(error, mini->stderr);
	ft_putstr_fd(": No such file or directory\n", mini->stderr);
	ft_reset_fds(mini);
	mini->exit = 1;
	return (-1);
}

static void	ft_free_array(char **array)
{
	int	j;

	j = 0;
	while (array[j])
	{
		free(array[j]);
		array[j] = NULL;
		j++;
	}
	free(array);
}

static char	**add_tmp_tolist(char *tmp, t_base *ptr, int i, int j)
{
	char	**new;

	new = (char **)malloc(sizeof(char *) * (ptr->size + 1));
	if (new == NULL)
		return (NULL);
	while (j < i)
	{
		new[j] = ft_strdup(ptr->av[j]);
		j++;
	}
	new[j] = tmp;
	j++;
	while (j < ptr->size)
	{
		new[j] = ft_strdup(ptr->av[j - 1]);
		j++;
	}
	new[j] = NULL;
	ft_free_array(ptr->av);
	return (new);
}

int	add_new_into_list(int j, t_base *ptr, int i)
{
	char	*tmp;
	char	*newav;

	tmp = NULL;
	if (j > 0)
	{
		tmp = ft_substr(ptr->av[i], 0, j);
		if (ptr->redir != 1 && numb_char(tmp, '\\') == (int)ft_strlen(tmp))
			tmp = ft_memmove(&tmp[0], &tmp[1], ft_strlen(tmp));
		newav = ptr->av[i];
		ptr->av[i] = ft_substr(newav, j, ft_strlen(newav) - j);
		free(newav);
	}
	if (i > 0)
	{
		ptr->size = ptr->size + 1;
		ptr->av = add_tmp_tolist(tmp, ptr, i, 0);
		if (ptr->av == NULL)
			return (-1);
	}
	return (0);
}

char	**ft_remove_redir_av(t_base *ptr, int i, int j)
{
	char	**temp;

	temp = (char **)malloc(sizeof(char *) * (ptr->size + 1));
	if (temp == NULL)
		return (NULL);
	while (j < i)
	{
		temp[j] = ft_strdup(ptr->av[j]);
		j++;
	}
	while (j < ptr->size)
	{
		temp[j] = ft_strdup(ptr->av[j + 2]);
		j++;
	}
	temp[j] = NULL;
	j = 0;
	while (ptr->av[j])
	{
		free(ptr->av[j]);
		ptr->av[j] = NULL;
		j++;
	}
	free(ptr->av);
	return (temp);
}
