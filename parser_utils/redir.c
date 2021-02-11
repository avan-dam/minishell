/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 14:34:29 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/02/11 10:55:53 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// CLEAN UP THIS FILE
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

static int	error_opening(char *error, t_mini *mini)
{
	ft_putstr_fd("bash: ", mini->stderr);
	ft_putstr_fd(error, mini->stderr);
	ft_putstr_fd(": No such file or directory\n", mini->stderr);
	ft_reset_fds(mini);
	mini->exit = 1;
	return (-1);
}

static int	ft_open_file(t_base *ptr, int i, t_mini *mini)
{
	// if ((ft_strchr_numb(tmp->argv[i + 1], '>', 0) != -1) ||
	// 	(ft_strchr_numb(tmp->argv[i + 1], '<', 0) != -1))
	// 		add_new_into_list()
	// printf("ptr->argv[i][%s]ptr->argv[i + 1][%s] will try open\n,", ptr->argv[i], ptr->argv[i + 1]);
	// ptr->argv[i + 1] = ft_check_dolla_quotes(ptr->argv[i + 1], mini, 0, 0); //FIXXXXXX!!!
	if (ptr->argv[i + 1] == NULL || ft_strcmp(ptr->argv[i + 1], ">") == 0)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", mini->stderr);
		ft_reset_fds(mini);
		mini->exit = 258; // check because this is what bash does but also exit code should not be above 255??
		// k = -1;
		return(-1);
	}
	if (ptr->redir == 0)
		return (i);
	if (ft_strcmp(">", ptr->argv[i]) == 0)
	{
		if ((mini->stdout = open(ptr->argv[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
		{	
			return(error_opening(ptr->argv[i + 1], mini));
			// error_opening(ptr->argv[i + 1], mini);
			// k = -1;
		}
		// printf("did open\n");
	}
	if (ft_strcmp(">>", ptr->argv[i]) == 0)
	{
		if ((mini->stdout = open(ptr->argv[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666)) == -1)
		{
			return(error_opening(ptr->argv[i + 1], mini));
			// error_opening(ptr->argv[i + 1], mini);
			// k = -1;
		}
	}
	if (ft_strcmp("<", ptr->argv[i]) == 0)
	{
		if ((mini->stdin = open(ptr->argv[i + 1], O_RDWR, 0666)) == -1)
		{	
			return(error_opening(ptr->argv[i + 1], mini));
			// error_opening(ptr->argv[i + 1], mini);
			// k = -1;
		}
		// printf("did open\n");
	}
	if (ft_remove_redir_argv(ptr, i, 0) == -1)
		return (-1);
	return (i);
	// return (k);
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

static int	add_new_into_list(int j, t_base *ptr, int i)
{
	char	*tmp;

	tmp = NULL;
	// printf("start off with now ptr->argv[i] is [%s] ptr->argv[i + 1] is [%s]\n", ptr->argv[i], ptr->argv[i + 1]);
	if (j > 0)
	{
		tmp = ft_substr(ptr->argv[i], 0, j);
		free(ptr->argv[i]);
		if (ptr->redir != 1 && numb_char(tmp, '\\') == (int)ft_strlen(tmp))
			tmp = ft_memmove(&tmp[0], &tmp[1], ft_strlen(tmp));
		ptr->argv[i] = ft_substr(ptr->argv[i], j, ft_strlen(ptr->argv[i]) - j);
	}
	if (i > 0)
	{
		ptr->size = ptr->size + 1;
		if ((ptr->argv = add_tmp_tolist(tmp, ptr, i, 0)) == NULL)
			return (-1);
		// printf("tmp just added is [%s]\n", tmp);
		// printf("and now ptr->argv[i] is [%s] ptr->argv[i + 1] is [%s]\n", ptr->argv[i], ptr->argv[i + 1]);
	}
	return (0);
}

static void	remove_extra_backslash_check_redir(t_base *ptr, int i)
{
	int 	j;

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

static char *ft_argvs_before_redirinto_string(t_base *ptr, int max)
{
	char	*tmp;
	char	*string;
	int		i;

	i = 0;
	tmp = ft_strdup("");
	string = NULL;
	// printf("max is %i and ptr->size is %i\n", i, ptr->size);
	while (i != max && ptr->argv[i])
	{
		// printf("is joining [%s] ptr->argv[i]\n", ptr->argv[i]);
		if (string)
			free(string);
		string = ft_strjoin(tmp, ptr->argv[i]);
		free(tmp);
		if (i + 1 != max)
        {
            if (ptr->argv[i + 1] && ptr->argv[i + 1][0] != '>' && ptr->argv[i + 1][0] != '<')
			{    
				tmp = ft_strdup(string);
				free(string);
				string = ft_strjoin(tmp, " ");
				free(tmp);
			}
        }
		tmp = ft_strdup(string);
		i++;
	}
	return (string);
}

static int	ft_backslash_redir(t_base *ptr, int i, t_mini *mini, int j)
{
	char	*tmp;

	remove_extra_backslash_check_redir(ptr, i);
	// printf("here\n");
	tmp = ft_argvs_before_redirinto_string(ptr, i);
	// printf("there\n");
	// printf("tmp is [%s]\n", tmp);
	if (tmp != NULL && ft_check_dolla_quotes(tmp, mini, 0, 1) == NULL)
	{
		// printf("in this\n");
		ptr->argv[i] = ft_check_dolla_quotes(ptr->argv[i], mini, 0, 2);
		ptr->redir = 4;
		return (0);
	}
	if (numb_char(ptr->argv[i], '\'') > 0 || numb_char(ptr->argv[i], '"') > 0)
	{
		ptr->argv[i] = ft_check_dolla_quotes(ptr->argv[i], mini, 0, 2);
		ptr->redir = 3;
		return (0);
	}
	while (ptr->argv[i][j] != '>' && ptr->argv[i][j] != '<')
		j++;
	if (j <= 0)
	{
		if (ptr->redir == 1)
		{
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
	t_base	*tmp;

	tmp = ptr;
	i = 0;
	tmp->redir = 0;
	t_base *tmpp = ptr;
	while (i < tmp->size && tmp->argv[i])
	{
		// printf("i is %d tmp->size is %d\n", i, tmp->size);
		// printf("1. tmp->argv[i][%s]\n", tmp->argv[i]);
		if ((ft_strchr_numb(tmp->argv[i], '>', 0) != -1) ||
		(ft_strchr_numb(tmp->argv[i], '<', 0) != -1))
		{
			if (ft_backslash_redir(tmp, i, mini, 0) == -1)
				return (NULL);
			if (tmp->redir == 1 && i != 0)
				i--;
			if (tmp->redir == 0)
				i++;
		}
		tmp->redir = 0;
		i++;
	}
	tmpp = tmp;
	return (tmp);
}

	// t_base *tmpp = ptr;
	// while(tmpp)
	// {
	// 	printf("AFTEr REDIR Argument HERE in list: tmpp->size%d\n", tmpp->size);
	// 	for (int k = 0; k < tmpp->size; k++)
	// 		printf("the argument: %s\n", tmpp->argv[k]);
	// 	printf("TYPE: %d\n", tmpp->type);
	// 	printf("SIZE: %d\n", tmpp->size);
	// 	printf("end of argument in list\n\n");
	// 	tmpp = tmpp->next;
	// }


// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   redir.c                                            :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: ambervandam <ambervandam@student.codam.      +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2021/02/02 14:34:29 by ambervandam   #+#    #+#                 */
// /*   Updated: 2021/02/10 14:35:09 by ambervandam   ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// // CLEAN UP THIS FILE
// // SO LOOK AT ALL > < and BACKSLASH

// static int	ft_remove_redir_argv(t_base *ptr, int i, int j)
// {
// 	char	**temp;

// 	ptr->size = ptr->size - 2;
// 	if ((temp = (char **)malloc(sizeof(char *) * (ptr->size + 1))) == NULL)
// 		return (-1);
// 	while (j < i)
// 	{
// 		temp[j] = ft_strdup(ptr->argv[j]);
// 		j++;
// 	}
// 	while (j < ptr->size)
// 	{
// 		temp[j] = ft_strdup(ptr->argv[j + 2]);
// 		j++;
// 	}
// 	temp[j] = NULL;
// 	j = 0;
// 	while (j < ptr->size + 2)
// 	{
// 		free(ptr->argv[j]);
// 		ptr->argv[j] = NULL;
// 		j++;
// 	}
// 	ptr->argv = temp;
// 	return (0);
// }

// static int	error_opening(char *error, t_mini *mini)
// {
// 	ft_putstr_fd("bash: ", mini->stderr);
// 	ft_putstr_fd(error, mini->stderr);
// 	ft_putstr_fd(": No such file or directory\n", mini->stderr);
// 	ft_reset_fds(mini);
// 	mini->exit = 1;
// 	return (-1);
// }

// static int	ft_open_file(t_base *ptr, int i, t_mini *mini)
// {
// 	// printf("ptr->argv[i][%s]ptr->argv[i + 1][%s] will try open\n,", ptr->argv[i], ptr->argv[i + 1]);
// 	// ptr->argv[i + 1] = ft_check_dolla_quotes(ptr->argv[i + 1], mini, 0, 0); //FIXXXXXX!!!
// 	if (ptr->argv[i + 1] == NULL || ft_strcmp(ptr->argv[i + 1], ">") == 0)
// 	{
// 		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", mini->stderr);
// 		ft_reset_fds(mini);
// 		mini->exit = 258; // check because this is what bash does but also exit code should not be above 255??
// 		// k = -1;
// 		return(-1);
// 	}
// 	if (ptr->redir == 0)
// 		return (i);
// 	if (ft_strcmp(">", ptr->argv[i]) == 0)
// 	{
// 		if ((mini->stdout = open(ptr->argv[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
// 		{	
// 			return(error_opening(ptr->argv[i + 1], mini));
// 			// error_opening(ptr->argv[i + 1], mini);
// 			// k = -1;
// 		}
// 		// printf("did open\n");
// 	}
// 	if (ft_strcmp(">>", ptr->argv[i]) == 0)
// 	{
// 		if ((mini->stdout = open(ptr->argv[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666)) == -1)
// 		{
// 			return(error_opening(ptr->argv[i + 1], mini));
// 			// error_opening(ptr->argv[i + 1], mini);
// 			// k = -1;
// 		}
// 	}
// 	if (ft_strcmp("<", ptr->argv[i]) == 0)
// 	{
// 		if ((mini->stdin = open(ptr->argv[i + 1], O_RDWR, 0666)) == -1)
// 		{	
// 			return(error_opening(ptr->argv[i + 1], mini));
// 			// error_opening(ptr->argv[i + 1], mini);
// 			// k = -1;
// 		}
// 		// printf("did open\n");
// 	}
// 	if (ft_remove_redir_argv(ptr, i, 0) == -1)
// 		return (-1);
// 	return (i);
// 	// return (k);
// }

// static char	**add_tmp_tolist(char *tmp, t_base *ptr, int i, int j)
// {
// 	char	**new;

// 	if ((new = (char **)malloc(sizeof(char *) * (ptr->size + 1))) == NULL)
// 		return (NULL);
// 	while (j < i)
// 	{
// 		new[j] = ft_strdup(ptr->argv[j]);
// 		j++;
// 	}
// 	new[j] = ft_strdup(tmp);
// 	j++;
// 	while (j < ptr->size)
// 	{
// 		new[j] = ft_strdup(ptr->argv[j - 1]);
// 		j++;
// 	}
// 	new[j] = NULL;
// 	j = 0;
// 	while (j < ptr->size - 1)
// 	{
// 		free(ptr->argv[j]);
// 		ptr->argv[j] = NULL;
// 		j++;
// 	}
// 	return (new);
// }

// static int	add_new_into_list(int j, t_base *ptr, int i)
// {
// 	char	*tmp;

// 	tmp = NULL;
// 	if (j > 0)
// 	{
// 		tmp = ft_substr(ptr->argv[i], 0, j);
// 		free(ptr->argv[i]);
// 		if (ptr->redir != 1 && numb_char(tmp, '\\') == (int)ft_strlen(tmp))
// 			tmp = ft_memmove(&tmp[0], &tmp[1], ft_strlen(tmp));
// 		ptr->argv[i] = ft_substr(ptr->argv[i], j, ft_strlen(ptr->argv[i]) - j);
// 	}
// 	if (i > 0)
// 	{
// 		ptr->size = ptr->size + 1;
// 		if ((ptr->argv = add_tmp_tolist(tmp, ptr, i, 0)) == NULL)
// 			return (-1);
// 	}
// 	return (0);
// }

// static void	remove_extra_backslash_check_redir(t_base *ptr, int i)
// {
// 	int 	j;

// 	j = 0;
// 	while (ptr->argv[i][j] == '\\')
// 		j++;
// 	if (j % 2 == 0)
// 		ptr->redir = 1;
// 	j = 0;
// 	while (ptr->argv[i][j] == '\\')
// 	{
// 		if (ptr->argv[i][j + 1] == '\\')
// 			ft_memmove(&ptr->argv[i][j], &ptr->argv[i][j + 1], ft_strlen(ptr->argv[i]) - j);
// 		j++;
// 	}
// }

// static char *ft_argvs_before_redirinto_string(t_base *ptr, int max)
// {
// 	char	*tmp;
// 	char	*string;
// 	int		i;

// 	i = 0;
// 	tmp = ft_strdup("");
// 	string = NULL;
// 	// printf("max is %i and ptr->size is %i\n", i, ptr->size);
// 	while (i != max && ptr->argv[i])
// 	{
// 		// printf("is joining [%s] ptr->argv[i]\n", ptr->argv[i]);
// 		if (string)
// 			free(string);
// 		string = ft_strjoin(tmp, ptr->argv[i]);
// 		free(tmp);
// 		if (i + 1 != max)
//         {
//             if (ptr->argv[i + 1] && ptr->argv[i + 1][0] != '>' && ptr->argv[i + 1][0] != '<')
// 			{    
// 				tmp = ft_strdup(string);
// 				free(string);
// 				string = ft_strjoin(tmp, " ");
// 				free(tmp);
// 			}
//         }
// 		tmp = ft_strdup(string);
// 		i++;
// 	}
// 	return (string);
// }

// static int	ft_backslash_redir(t_base *ptr, int i, t_mini *mini, int j)
// {
// 	char	*tmp;

// 	remove_extra_backslash_check_redir(ptr, i);
// 	// printf("here\n");
// 	tmp = ft_argvs_before_redirinto_string(ptr, i);
// 	// printf("there\n");
// 	// printf("tmp is %s]\n", tmp);
// 	if (tmp != NULL && ft_check_dolla_quotes(tmp, mini, 0, 1) == NULL)
// 	{
// 		// printf("in this\n");
// 		ptr->argv[i] = ft_check_dolla_quotes(ptr->argv[i], mini, 0, 2);
// 		ptr->redir = 4;
// 		return (0);
// 	}
// 	if (numb_char(ptr->argv[i], '\'') > 0 || numb_char(ptr->argv[i], '"') > 0)
// 	{
// 		ptr->argv[i] = ft_check_dolla_quotes(ptr->argv[i], mini, 0, 2);
// 		ptr->redir = 3;
// 		return (0);
// 	}
// 	while (ptr->argv[i][j] != '>' && ptr->argv[i][j] != '<')
// 		j++;
// 	if (j <= 0)
// 	{
// 		if (ptr->redir == 1)
// 		{
// 			if (ft_open_file(ptr, i, mini) == -1)
// 				return (-1);
// 			return (0);
// 		}
// 	}
// 	if (add_new_into_list(j, ptr, i) == -1)
// 		return (-1);
// 	return (0);
// }

// t_base		*ft_redir(t_mini *mini, t_base *ptr)
// {
// 	int		i;
// 	t_base	*tmp;

// 	tmp = ptr;
// 	i = 0;
// 	tmp->redir = 0;
// 	t_base *tmpp = ptr;
// 	while(tmpp)
// 	{
// 		printf("entering REDIR Argument HERE in list: tmpp->size%d\n", tmpp->size);
// 		for (int k = 0; k < tmpp->size; k++)
// 			printf("the argument: %s\n", tmpp->argv[k]);
// 		printf("TYPE: %d\n", tmpp->type);
// 		printf("SIZE: %d\n", tmpp->size);
// 		printf("end of argument in list\n\n");
// 		tmpp = tmpp->next;
// 	}
// 	while (i < tmp->size && tmp->argv[i])
// 	{
// 		// printf("i is %d tmp->size is %d\n", i, tmp->size);
// 		// printf("tmp->argv[i][%s]\n", tmp->argv[i]);
// 		if ((ft_strchr_numb(tmp->argv[i], '>', 0) != -1) ||
// 		(ft_strchr_numb(tmp->argv[i], '<', 0) != -1))
// 		{
// 			if (ft_backslash_redir(tmp, i, mini, 0) == -1)
// 				return (NULL);
// 			if (tmp->redir == 1 && i != 0)
// 				i--;
// 			if (tmp->redir == 0)
// 				i++;
// 		}
// 		tmp->redir = 0;
// 		i++;
// 	}
// 	tmpp = tmp;
// 	while(tmpp)
// 	{
// 		printf("leaving REDIR Argument HERE in list: tmpp->size%d\n", tmpp->size);
// 		for (int k = 0; k < tmpp->size; k++)
// 			printf("the argument: %s\n", tmpp->argv[k]);
// 		printf("TYPE: %d\n", tmpp->type);
// 		printf("SIZE: %d\n", tmpp->size);
// 		printf("end of argument in list\n\n");
// 		tmpp = tmpp->next;
// 	}
// 	return (tmp);
// }

// 	// t_base *tmpp = ptr;
// 	// while(tmpp)
// 	// {
// 	// 	printf("AFTEr REDIR Argument HERE in list: tmpp->size%d\n", tmpp->size);
// 	// 	for (int k = 0; k < tmpp->size; k++)
// 	// 		printf("the argument: %s\n", tmpp->argv[k]);
// 	// 	printf("TYPE: %d\n", tmpp->type);
// 	// 	printf("SIZE: %d\n", tmpp->size);
// 	// 	printf("end of argument in list\n\n");
// 	// 	tmpp = tmpp->next;
// 	// }
