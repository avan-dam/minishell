/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_adapt_array.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 09:38:57 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/02/17 09:42:56 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_array(char **array)
{
	int j;

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
	ft_free_array(ptr->argv);
	return (new);
}

int			add_new_into_list(int j, t_base *ptr, int i)
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

char		**ft_remove_redir_argv(t_base *ptr, int i, int j)
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
