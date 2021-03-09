/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_av_list.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/04 11:10:44 by avan-dam      #+#    #+#                 */
/*   Updated: 2021/03/09 17:04:19 by avan-dam      ########   odam.nl         */
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
	// printf("mini->cmd_part is [%s]\n", mini->cmd_part);
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
			&& result != NULL)
		{
			// printf("in break\n");
				break ;
		}
		free(result);
		result = mem_check_tkns(ft_substr(mini->cmd_part, k, j - k + 1), mini, 0, 4);
		j++;
	}
	if (result)
		free(result);
	// printf("returns values %d\n", j);
	return (j);
}

int	fill_av_list(t_base *new, t_mini *mini, int j, int l)
{
	int		k;
	char	*temp;

	k = 0;
	while (l != new->size)
	{
		// printf("new->size is %d\n", new->size);
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
			temp = new->av[l];
			// printf("new->av[l][%s]\n", new->av[l]);
			if (check_tokens(temp, mini, 0, 0) == NULL)
				return (-1);
		}
		l++;
	}
	return (0);
}

static int	more_av_list(t_base *new, t_mini *mini, t_base **ptr, char *line)
{
	new->size = mini->numb_cmds;
	new->prev = NULL;
	new->next = NULL;
	new->av[mini->numb_cmds] = NULL;
	if (fill_av_list(new, mini, 0, 0) == -1)
	{
		free(line);
		return (-1);
	}
	new->type = mini->type_end;
	if (new->av[0][0] != '$')
	new->av[0] = ft_strtolower(new->av[0]);
	ft_lstadd_back_base(ptr, new);
	free(line);
	return (0);
}

int	create_av_list(t_base **ptr, char *line, t_mini *mini)
{
	int		numb_characters;
	t_base	*new;

	if (mini->cmd_part)
		free(mini->cmd_part);
	numb_characters = no_of_commands(line, mini, 0, 1);
	new = (t_base *)malloc(sizeof(t_base));
	if (new == NULL)
		return (-1);
	new->av = (char **)malloc(sizeof(char *) * (mini->numb_cmds + 1));
	if (new->av == NULL)
		return (-1);
	if (more_av_list(new, mini, ptr, line) == -1)
		return (-1);
	return (numb_characters);
}
