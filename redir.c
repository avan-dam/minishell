/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ambervandam <ambervandam@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/12 13:52:12 by ambervandam   #+#    #+#                 */
/*   Updated: 2021/01/21 00:40:05 by ambervandam   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function finds the first thing behind 
// filenam canytt hsavespaceat start or end
static void	ft_set_start(t_redir *r, t_mini *mini)
{
	int i;
	char *fdtoredir;
	
	// printf("before changing in start mini->more is [%s]\n",mini->more);
	r->fdtoredir = 0;
	if ((r->j < r->i && r->j != -1) || (r->i == -1 && r->j != -1))
	{
		// printf("mini->more is [%s]in swap with r.j%d as and r.i%d as \n", mini->more, r.j, r.i);
		r->i = r->j;
		r->k = 1;
	}
	r->filename = ft_substr(mini->more, r->i + 1, ft_strlen(mini->more) - r->i - 1);
	mini->more = ft_substr(mini->more, 0, r->i);
	r->filename = ft_strtrim(r->filename, " ");
	mini->more = ft_strtrim(mini->more, " ");
	r->m_files = ft_strdup(r->filename);
	i = ft_strlen(mini->more) - 1;
	// printf("i is %d and c there is [%c]\n", i, mini->more[i]);
	while (i >= 0 && ((mini->more[i] == '&') || (mini->more[i] >= '0' && mini->more[i] <= '9')))
		i--;
	// printf("and i now is %d\n", i);
	if (i != (int)ft_strlen(mini->more) - 1)
	{
		fdtoredir = ft_substr(mini->more, i + 1, ft_strlen(mini->more) - i + 1);
		// printf("\n\nfdtoredir is [%s] mini->more[%s]", fdtoredir, mini->more);
		if (ft_strcmp(fdtoredir, "&") == 0)
			r->fdtoredir = -2;
		else
			r->fdtoredir = ft_atoi(fdtoredir);
		mini->more = ft_substr(mini->more, 0, i);
	}
	if (r->filename[0] == '&')
	{
		r->fdtoredir = -2;
		r->filename = ft_substr(r->filename, 1, ft_strlen(r->filename) - 1);
	}
	// printf("r->fdtoredir [%d] and mini->more[%s]\n", r->fdtoredir, mini->more);
}

static void	ft_check_values(t_redir *r, t_mini *mini)
{
	if (r->filename == NULL)
	{
		r->filename = mini->more;
		mini->more = NULL;
	}
	if (r->filename[0] == '>')
	{
		if (r->filename[1] == '&')
		{
			r->error = ft_strdup("unexpected token `&'");
			return ;
		}
		r->filename = ft_substr(r->filename, 1, ft_strlen(r->filename) - 1);
		r->d = 1;
	}
	if ((r->i = ft_strchr_numb(r->m_files, '>', 0)) != -1)
	{
		r->filename = ft_substr(r->m_files, 0, r->i);
		r->m_files = ft_substr(r->m_files, r->i + 1, ft_strlen(r->m_files) - r->i - 1);
	}
	else
		r->m_files = ft_strdup("");
	r->filename = ft_strtrim(r->filename, " ");
}

static void	ft_check_alpha(t_redir *r, t_mini *mini)
{
	// printf("\n\nin alpha function with && mini->more[%s] r->filename[%s], r->m_files[%s] r->error[%s] and r->d[%d] and r->k[%d] r->alpha[%d]\n", mini->more, r->filename, r->m_files, r->error, r->d, r->k, r->alpha);
	r->filename = ft_substr(r->filename, 1, ft_strlen(r->filename) - 1);
	// printf("now file name is %s\n", r->filename);
	r->alpha = 1;
	if (r->k == 0)
	{
		// printf("before atoi mini->stdout is %d and stderr is %d\n", mini->stdout, mini->stderr);
		// printf("before atoi r->fdtoredir%d\n", r->fdtoredir);
		if ((r->fdtoredir == 2 || r->fdtoredir == -2) && ft_strcmp(r->filename, "1") == 0)
			mini->stderr = mini->stdout;
		else
			mini->stdout = ft_atoi(r->filename);
		// printf("after atoi mini->stdout is %d and stderr is %d\n", mini->stdout, mini->stderr);
	}
	if (r->k == 1)
	{
		mini->stdin = ft_atoi(r->filename);
		if (mini->stdin >= 3)
		{
			r->error = ft_strdup("Bad file descriptor");
			return ;
		}
	}
	//if breaking take out the r->filename = ""
	r->filename = "";
	r->fdtoredir = 0;
}

static void	open_function(t_redir *r, t_mini *mini)
{
	int		i;
	char	*filename;
	
	filename = ft_strdup(r->filename);
	if ((i = ft_strchr_numb(r->filename, ' ', 0)) != -1)
		filename = ft_substr(r->filename, 0, i);
	// printf("\nin open function with filename%s && mini->more[%s] r->error[%s] and r->d[%d] and r->k[%d] and r->alpha%d and r->fdtoredir%d && r->filename[%s]\n", filename, mini->more, r->error, r->d, r->k, r->alpha, r->fdtoredir, r->filename);
	if (r->error == NULL)
	{
		if (r->d == 0 && r->k == 0 && r->fdtoredir != 2)
		{
			// printf("I am about to open filename[%s] for stdout is now %d\n", filename, mini->stdout);
			mini->stdout = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
			// printf("stdout is now %d\n", mini->stdout);
		}
		if ((r->d == 0 && r->k == 0) && (r->fdtoredir == 2 || r->fdtoredir == -2))
		{
			// printf("I am about to open r->filename[%s] for stderr is now %d\n", r->filename, mini->stderr);
			mini->stderr = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
			// printf("stderr is now %d\n", mini->stderr);
		}
		//for >> so i can append not truncate
		if (r->d == 1 && r->k == 0)
			mini->stdout = open(filename, O_RDWR | O_CREAT | O_APPEND, 0666);
		if (r->k == 1)
		{
			if ((r->fd = open(filename, O_RDWR, 0666)) == -1)
			{
				r->error = ft_strdup("No such file or directory");
				return ;
			}
			mini->stdin = r->fd;
		}
		// printf("\nopendone\n");
	}
}

static void	ft_reset_values(t_redir *r, t_mini *mini)
{
	int i;
	
	i = ft_strlen(r->filename) - 1;
	while (i >= 0 && ((r->filename[i] == '&') || (r->filename[i] >= '0' && r->filename[i] <= '9')))
		i--;
	if (i != (int)ft_strlen(r->filename) - 1)
	r->fdtoredir = ft_atoi(ft_substr(r->filename, i + 1, ft_strlen(r->filename) - i + 1));
	if (mini->more != NULL)
	{
		if (ft_strcmp("", mini->more) == 0)
			mini->more = NULL;
	}
	r->filename = ft_strdup(r->m_files);
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
}

int			ft_redir(t_mini *mini)
{
	t_redir r;

	ft_memset(&r, 0, sizeof(r));
	r.j = ft_strchr_numb(mini->more, '<', 0);
	r.i = ft_strchr_numb(mini->more, '>', 0);
	// printf("in redir with mini->stdout%d mini->stdin%d mini->stderr%d", mini->stdout, mini->stdin, mini->stderr);
	// printf("minicommand [%s] mini->more [%s] filename[%s], m_files[%s], error[%s], fd[%d], alpha[%d]\n", mini->command, mini->more, r.filename, r.m_files, r.error, r.fd, r.alpha);
	while (r.j != -1 || r.i != -1)
	{
		ft_set_start(&r, mini);
		// printf("\n\nafter set start minicommand [%s] mini->more[%s] filename[%s], m_files[%s], error[%s], fd[%d], alpha[%d]\n", mini->command, mini->more, r.filename, r.m_files, r.error, r.fd, r.alpha);
		while (ft_strcmp(r.m_files, "") != 0)
		{
			// printf("stdin is now %d stdout is now %d and stderror is now %d",mini->stdin, mini->stdout, mini->stderr);
			// printf("and  function with && mini->more[%s] r->filename[%s], r->m_files[%s] r->error[%s] and r->d[%d] and r->k[%d]\n", mini->more, r.filename, r.m_files, r.error, r.d, r.k);
			ft_check_values(&r, mini);
			// printf("now after check r->filename[%s], r->m_files[%s] values is now %d stdout is now %d and stderror is now %d",r.filename, r.m_files, mini->stdin, mini->stdout, mini->stderr);
			if (r.filename[0] == '&' && r.error == NULL)
				ft_check_alpha(&r, mini);
			else
				open_function(&r, mini);
			// printf("minicommand [%s] mini->more[%s] filename[%s], m_files[%s], error[%s], fd[%d], alpha[%d]\n", mini->command, mini->more, r.filename, r.m_files, r.error, r.fd, r.alpha);
			if (r.error != NULL)
				return (unvalid_identifier(r.error, mini));
			// printf("before reset after check r->filename[%s], r->m_files[%s] values is now %d stdout is now %d and stderror is now %d\n",r.filename, r.m_files, mini->stdin, mini->stdout, mini->stderr);
			ft_reset_values(&r, mini);
			// printf("after reset after check r->filename[%s], r->m_files[%s] values is now %d stdout is now %d and stderror is now %d\n",r.filename, r.m_files, mini->stdin, mini->stdout, mini->stderr);
		}
		free(r.filename);
		free(r.m_files);
	}
	ft_memset(&r, 0, sizeof(r));
	return (0);
}
