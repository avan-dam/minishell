/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 22:27:08 by salbregh      #+#    #+#                 */
/*   Updated: 2020/12/14 11:46:11 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// // rewrite getenv() setenv()

// // gcc -o env env.c

// int		main(int argc, char **argv, char **envp)
// {
// 	for (int i = 0; envp[i] != NULL; i++)
// 	{
// 		printf("%d: %s\n", i, envp[i]);
// 	}
// }

static int  ft_find_start_var(char *more, int i, int position)
{
    int j;
    int k;

    k = 0;
    j = 0;
    if (position == 0)
    {
    	while (j < i)
    	{
            if (more[j] == ' ')
                k = j;
            j++;
        }
        if (k != 0)
            k++;
		return (k);
    }
	if (position == 1)
	{
		while (more[i] != '\0')
		{
			if (more[i] == ' ')
				return (i);
			i++;
		}
		return (i);
	}
    return (-1);
}

static int ft_strrch_equal(char *line)
{
    int i;

    i = 0;
    while (line[i] != '\0')
    {
        if (line[i] == '=')
        {
            return (i);
        }
		i++;
    }
    return (-1);
}

static int  ft_split_env(t_mini *mini, char *line, t_list *env)
{
    int     i;
    int     j;
    char	*var1;
    char	*var2;

    j = 0;
    if ((i = ft_strrch_equal(line)) == -1)
        return (0);
    if (line[i - 1] == ' ' || line[i + 1] == ' ')
        return (0);
    j = ft_find_start_var(line, i, 0);
    var1 = ft_substr(line, j, i - j);
	j = ft_find_start_var(line, i, 1);
	var2 = ft_substr(line, i + 1, j - i - 1);
	// if (ft_check_var1_already_in_list(var1, var2, mini) == 1)
    // {
    //     ft_lstprint(mini->tlist);
    //     return (1);
    // }
    env = ft_lstnew(var1, var2);
    ft_lstadd_back(&mini->tlist, env);
    return (1);
}

void	ft_set_env(char **argv, char **envp, t_mini *mini)
{
	int		i;
	t_list	*env;

	i = 0;
	env = NULL;
	(void)argv; // check for correct name executable?
	while (envp[i] != NULL)
	{
		ft_split_env(mini, envp[i], env);
		i++;
	}
	ft_lstprint(mini->tlist);
}
