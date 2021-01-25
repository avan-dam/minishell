/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/12 13:52:12 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/25 15:51:35 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function finds the first thing behind 
// filenam canytt hsavespaceat start or end
static void	ft_set_start(t_redir *r, t_mini *mini)
{
	int i;
	char *fd;
	
	if ((r->j < r->i && r->j != -1) || (r->i == -1 && r->j != -1))
	{
		r->i = r->j;
		r->redirinput = 1;
	}
	r->file = ft_substr(mini->more, r->i + 1, ft_strlen(mini->more) - r->i - 1);
	mini->more = ft_substr(mini->more, 0, r->i);
	r->file = ft_strtrim(r->file, " ");
	mini->more = ft_strtrim(mini->more, " ");
	r->m_files = ft_strdup(r->file);
	i = ft_strlen(mini->more) - 1;
	while (i >= 0 && ((mini->more[i] == '&') || (mini->more[i] >= '0' && mini->more[i] <= '9')))
	// while (i >= 0 && (mini->more[i] >= '0' && mini->more[i] <= '9'))
		i--;
	if (i != (int)ft_strlen(mini->more) - 1)
	{
		fd = ft_substr(mini->more, i + 1, ft_strlen(mini->more) - i + 1);
		if (ft_strcmp(fd, "&") == 0)
			r->fd = -2;
		else
			r->fd = ft_atoi(fd);
		mini->more = ft_substr(mini->more, 0, i);
	}
	if (r->file[0] == '&')
	{
		r->fd = -2;
		r->alpha = 1;
		r->file = ft_substr(r->file, 1, ft_strlen(r->file) - 1);
	}
	if (ft_strcmp(r->m_files, "") == 0)
	{
		r->i = -1;
		r->j = -1;
	}
}

static void	ft_check_values(t_redir *r, t_mini *mini)
{
	if (r->file == NULL)
	{
		r->file = mini->more;
		mini->more = NULL;
	}
	if (r->file[0] == '>')
	{
		if (r->file[1] == '&')
		{
			r->error = ft_strdup("bash: syntax error near unexpected token `&'\n");
			mini->exit = 258;
			return ;
		}
		r->file = ft_substr(r->file, 1, ft_strlen(r->file) - 1);
		r->d = 1;
	}
	if (r->file[0] == '&' && r->file[1] == '\0')
	{
		r->error = ft_strdup("bash: syntax error near unexpected token `newline'\n");
		mini->exit = 258;
		return ;
	}
	if (r->file[0] == '$')
	{
		r->error = ft_strjoin(r->file, ": ambiguous redirect\n");
		mini->exit = 1;
		return ;
	}
	if ((r->i = ft_strchr_numb(r->m_files, '>', 0)) != -1)
	{
		r->file = ft_substr(r->m_files, 0, r->i);
		r->m_files = ft_substr(r->m_files, r->i + 1, ft_strlen(r->m_files) - r->i - 1);
	}
	else
		r->m_files = ft_strdup("");
	r->file = ft_strtrim(r->file, " ");
}

static void	ft_check_alpha(t_redir *r, t_mini *mini)
{
	r->alpha = 1;
	if (ft_atoi(r->file) >= 3)
	{
			mini->exit = 1;
			r->error = ft_strjoin("bash: ", r->file);
			r->error = ft_strjoin(r->error, ": Bad file descriptor\n");
			return ;
	}
	if (r->redirinput == 0)
	{
		if ((r->fd == 2 || r->fd == -2) && ft_strcmp(r->file, "1") == 0)
			mini->stderr = mini->stdout;
		else if (ft_atoi(r->file) < 3)
			mini->stdout = ft_atoi(r->file);
	}
	if (r->redirinput == 1)
	{
		mini->stdin = ft_atoi(r->file);
		if (r->file[0] == '<' && r->file[1] == '&')
		{
			mini->exit = 258;
			r->error = ft_strdup("bash: syntax error near unexpected token `&'\n");
			return ;
		}
	}
	r->file = "";
	r->fd = 0;
}

static void	open_function(t_redir *r, t_mini *mini)
{
	int		i;
	char	*file;

	file = ft_strdup(r->file);
	if ((i = ft_strchr_numb(r->file, ' ', 0)) != -1)
		file = ft_substr(r->file, 0, i);
	if (r->error == NULL)
	{
		if (r->d == 0 && r->redirinput == 0 && r->fd != 2)
			mini->stdout = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
		if ((r->d == 0 && r->redirinput == 0) && (r->fd == 2 || r->fd == -2))
			mini->stderr = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
		//for >> so i can append not truncate
		if (r->d == 1 && r->redirinput == 0)
			mini->stdout = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
		if (r->redirinput == 1)
		{
			if ((i = open(file, O_RDWR, 0666)) == -1)
			{
				r->error = ft_strjoin(file, ": ambiguous redirect\n");
				mini->exit = 1;
				return ;
			}
			mini->stdin = i;
		}
	}
}

static void	ft_reset_values(t_redir *r, t_mini *mini)
{
	int i;

	i = ft_strlen(r->file) - 1;
	while (i >= 0 && ((r->file[i] == '&') || (r->file[i] >= '0' && r->file[i] <= '9')))
		i--;
	if (i != (int)ft_strlen(r->file) - 1)
		r->fd = ft_atoi(ft_substr(r->file, i + 1, ft_strlen(r->file) - i + 1));
	if (mini->more != NULL)
	{
		if (ft_strcmp("", mini->more) == 0)
			mini->more = NULL;
	}
	r->file = ft_strdup(r->m_files);
	if (mini->more == NULL)
	{
		r->j = -1;
		r->i = -1;
	}
	else
	{
		r->j = ft_strchr_numb(mini->more, '<', 0);
		r->i = ft_strchr_numb(mini->more, '>', 0);
	}
	r->fd = 0;
}

int			ft_redir(t_mini *mini)
{
	t_redir r;

	ft_memset(&r, 0, sizeof(r));
	r.j = ft_strchr_numb(mini->more, '<', 0);
	r.i = ft_strchr_numb(mini->more, '>', 0);
	while (r.j != -1 || r.i != -1)
	{
		// printf("before set mini->more[%s] r.file[%s], r.m_files[%s], r.error[%s], r.i%d, r.d%d, r.redirinput%d, r.j%d, r.fd%d, r.alpha%d\n", mini->more, r.file, r.m_files, r.error, r.i, r.d, r.redirinput, r.j, r.fd, r.alpha);
		ft_set_start(&r, mini);
		while (ft_strcmp(r.m_files, "") != 0)
		{
			ft_check_values(&r, mini);
			if ((r.file[0] == '&' || r.alpha == 1 || (r.file[0] == '<' && r.file[1] == '&')) && r.error == NULL)
				ft_check_alpha(&r, mini);
			else
				open_function(&r, mini);
			if (r.error != NULL)
			{
				ft_putstr_fd(r.error, mini->stderr);
				return (-1);
			}
			ft_reset_values(&r, mini);
		}
		free(r.file);
		free(r.m_files);
	}
	ft_memset(&r, 0, sizeof(r));
	return (0);
}
