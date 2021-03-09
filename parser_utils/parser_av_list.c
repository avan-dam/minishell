/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_av_list.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/04 11:10:44 by avan-dam      #+#    #+#                 */
/*   Updated: 2021/03/09 14:15:01 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
static int	ft_begin(const char *s1, char c)
{
	int		i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != c)
			return (i);
		i++;
	}
	return (i);
}

static int	fT_END(const char *s1, char c)
{
	int		i;
	int		inset;

	i = ft_strlen(s1) - 1;
	inset = 0;
	while (i >= 0)
	{
		if (s1[i] != c || i == 0 || s1[i - 1] == '\\')
			return (i);
		i--;
	}
	return (i);
}

char	*ft_strtrim_backslash(char const *s1, char c)
{
	int		i;
	int		begin;
	int		end;
	char	*newstr;

	if (s1 == NULL)
		return (NULL);
	begin = ft_begin(s1, c);
	end = fT_END(s1, c);
	if (begin > end)
		return (ft_strdup(""));
	newstr = (char *)malloc(sizeof(char) * (end - begin + 2));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (begin <= end)
	{
		newstr[i] = s1[begin];
		i++;
		begin++;
	}
	newstr[i] = '\0';
	return (newstr);
}
static int 	fill_av_more(t_mini *mini, int j, int k)
{
	char *result;
	char *temp;

	temp = mini->cmd_part;
	mini->cmd_part = ft_strtrim_backslash(temp, ' ');
	free(temp);
	// printf("before\n");
	result = mem_check_tkns(ft_substr(mini->cmd_part, k, j - k + 1), mini, 0, 4);
	while (mini->cmd_part[j] && 
		((mini->cmd_part[j] != ' ' ||  (mini->cmd_part[j] != ' ' && mini->cmd_part[j + 1] != '\\'))
		|| result == NULL))
		{
			free(result);
			result = mem_check_tkns(ft_substr(mini->cmd_part, k, j - k + 1), mini, 0, 4);
		if ((mini->cmd_part[j] == '>' || mini->cmd_part[j] == '<')
			&& mini->cmd_part[j + 1] != '\''
			&& mini->cmd_part[j + 1] != '>'
			&& mini->cmd_part[j + 1] != '"' && result != NULL)
		{
				break ;
		}
		free(result);
		result = mem_check_tkns(ft_substr(mini->cmd_part, k, j - k + 1), mini, 0, 4);
		j++;
	}
		// printf("after \n");
	if (result)
		free(result);
	return (j);
}

void	fill_av_list(t_base *new, t_mini *mini, int j, int l)
{
	int		k;
	char	*temp;

	k = 0;
	while (l != new->size)
	{
		if (mini->cmd_part[j] == '\0')
			new->av[l] = NULL;
		else
		{
			while (mini->cmd_part[j] == ' ')
				j++;
			k = j;
			j = fill_av_more(mini, j, k);
			if ((mini->cmd_part[j] == '>' || (mini->cmd_part[j] == '<'
				&& mini->cmd_part[j + 1] != '>')))
			{
				new->av[l] = ft_substr(mini->cmd_part, k, j - k + 1);
				j++;
			}
			else
				new->av[l] = ft_substr(mini->cmd_part, k, j - k);
			// printf("new->av[l][%s]\n", new->av[l]);
			temp = new->av[l];
			new->av[l] = mem_check_tkns(temp, mini, 0, 0);
			// printf("2new->av[l][%s]\n", new->av[l]);
			if (new->av[l] == NULL)
			{
				// printf("in this\n");
				return ;
			} // do something return -1
		}
		l++;
	}
}

static void	more_av_list(t_base *new, t_mini *mini, t_base **ptr, char *line)
{
	new->size = mini->numb_cmds;
	new->prev = NULL;
	new->next = NULL;
	new->av[mini->numb_cmds] = NULL;
	fill_av_list(new, mini, 0, 0);
	new->type = mini->type_end;
	new->av[0] = ft_strtolower(new->av[0]);
	ft_lstadd_back_base(ptr, new);
	free(line);
}

int	create_av_list(t_base **ptr, char *line, t_mini *mini)
{
	int		numb_characters;
	t_base	*new;
	// char	*temp;

	// printf("in av list create\n");
	if (mini->cmd_part)
		free(mini->cmd_part);
	numb_characters = no_of_commands(line, mini, 0, 1);
	// temp = mini->cmd_part;
	// mini->cmd_part = mem_check_tkns(temp, mini, 0, 0);
	// if (mini->cmd_part == NULL)
	// 	return (-1);
	new = (t_base *)malloc(sizeof(t_base));
	if (new == NULL)
		return (-1);
	new->av = (char **)malloc(sizeof(char *) * (mini->numb_cmds + 1));
	if (new->av == NULL)
		return (-1);
	more_av_list(new, mini, ptr, line);
	return (numb_characters);
}
