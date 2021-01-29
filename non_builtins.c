/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   non_builtins.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/28 15:06:53 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/28 17:41:37 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

/*
**  play around with opendir, closedir and readdir
**	finding all the /bin /usr/bin functions
*/

static int		ft_check_in_usr_bin(t_base *ptr, struct dirent *dit, DIR *dirp)
{
	t_base		*tmp;

	tmp = ptr;
	tmp->argv[0] = ft_strtrim(tmp->argv[0], "/usr/bin/");
	while ((dit = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(dit->d_name, tmp->argv[0]) == 0)
		{
			tmp->argv[0] = ft_strjoin("/usr/bin/", tmp->argv[0]);
			ptr->argv[0] = tmp->argv[0]; // free ptr->argv?
			closedir(dirp);
			return (0);
		}
	}
	return (1);
}

static int		ft_check_in_bin(t_base *ptr, struct dirent *dit, DIR *dirp)
{
	t_base		*tmp;

	tmp = ptr;
	tmp->argv[0] = ft_strtrim(tmp->argv[0], "/bin/");
	while ((dit = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(dit->d_name, tmp->argv[0]) == 0)
		{
			tmp->argv[0] = ft_strjoin("/bin/", tmp->argv[0]);
			ptr->argv[0] = tmp->argv[0];
			closedir(dirp);
			return (0);
		}
	}
	return (1);
}

int				look_for_non_builtin(t_base *ptr)
{
	DIR				*dirp; // dir pointer
	struct dirent	*dit;

	dit = NULL;
	if ((dirp = opendir("/bin")) == NULL) // opens the directory and points to the first entry in the directory	
		exit(0); // change
	if (ft_check_in_bin(ptr, dit, dirp) == 0)
		return (0);
	closedir(dirp);
	if ((dirp = opendir("/usr/bin")) == NULL)
		exit (0); // change
	if (ft_check_in_usr_bin(ptr, dit, dirp) == 0)
		return (0);
	if (closedir(dirp) == -1)
		exit (0); // change
	return (1);
}
