/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_adapt_array.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 09:38:57 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/04/15 10:46:48 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (tmp == NULL)
	{
		ft_free_array(ptr->av);
		return (new);
	}
	j++;
	while (j < ptr->size && ptr->av[j - 1])
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
	char	*tempptr;

	tmp = NULL;
	if (j > 0)
	{
		tmp = ft_substr(ptr->av[i], 0, j);
		if (ptr->redir != 1 && nb_str(tmp, '\\') == (int)ft_strlen(tmp))
			tmp = ft_memmove(&tmp[0], &tmp[1], ft_strlen(tmp));
		newav = ptr->av[i];
		ptr->av[i] = ft_substr(newav, j, ft_strlen(newav) - j);
		if (i == 0)
		{
			tempptr = ptr->av[i];
			ptr->av[i] = ft_strtrim_backslash(tempptr, ' ');
			free(tempptr);
		}
		free(newav);
	}
	ptr->size = ptr->size + 1;
	ptr->av = add_tmp_tolist(tmp, ptr, i, 0);
	if (ptr->av == NULL)
		return (-1);
	return (0);
}

int	find_k(t_base *ptr)
{
	int	k;

	k = 2;
	ptr->size = ptr->size - 2;
	if (ptr->prev && ptr->prev->type == T_PIPE)
	{	
		ptr->size++;
		k--;
	}
	return (k);
}

char	**ft_remove_redir_av(t_base *ptr, int i, int j, int k)
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
	while (ptr->av[j + k] && j < ptr->size)
	{
		temp[j] = ft_strdup(ptr->av[j + k]);
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
