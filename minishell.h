/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-dam <avan-dam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/03 17:50:50 by avan-dam      #+#    #+#                 */
/*   Updated: 2021/01/20 18:51:25 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/syslimits.h> // not sure if allowed?
# include <fcntl.h>

# define STDIN		0
# define STDOUT		1
# define STDERR		2
# define TYPE_END	3
# define TYPE_PIPE	4
# define TYPE_BREAK	5

typedef struct		s_base
{
	char			**argv;
	int				size;
	int				type;
	int				fd[2];
	struct s_base	*prev;
	struct s_base	*next;
}					t_base;

typedef struct		s_line
{
	int				o;
	int				t;
	int				k;
	char			*line;
}					t_line;

typedef struct		s_list
{
	char			*var1;
	char			*var2;
	struct s_list	*next;
}					t_list;

typedef struct		s_mini
{
	char			*command;
	char			*more;
	t_list			*run2;
	char			*currentpwd;
	char			*oldpwd;
	t_list			*env1;
	// builtin and execve arrray need corresponding function array for this
	char			*builtin[8];
	char			*notbuiltin[13]; // ls mkdir touch cat
	int				stdout;
	int				stderr;
	int				numb_cmds; // Command counter new struct
	char 			*cmd_part;
}					t_mini;

typedef struct		s_piper
{
	int				check;
	char			*write_side;
	char			*read_side;
	int				fd[2]; // fd[0] - read fd[1] - write made by pipe(fd);
}					t_piper;

int					ft_start_parsing(char *line, t_mini *mini, char **envp); // new
int					ft_echo(char *string, t_mini *mini, t_piper *piper);
void				ft_putstr(char *s);
int				    ft_export(t_mini *mini, char *more);
char				*ft_check_dolla_quotes(char *line, t_mini *mini, int i);
int 				ft_unset(t_mini *mini, char *unset);
int					unvalid_identifier(char *error, t_mini *mini);
int 				ft_strchr_numb(char *line, char c, int i);
int					ft_strrchr_numb(char *line, char c, int i);
int  				numb_char(char *line, char c);
int  				ft_split_into_tlist(t_mini *mini, char *line);
t_list				*ft_lstnew(void *var1, void *var2);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstprint(t_list *lst, t_mini *mini);
// int					ft_builtin(t_mini *mini, char *command, char *more, char **envp);
int					ft_execve(t_mini *mini, char **envp, t_piper *piper);
void				ft_lstclear(t_list **lst);
int					ft_redir(t_mini *mini, int d);

void				ft_cd(t_mini *mini);
void				ft_add_env(char *env, char *path, t_mini *mini); // or static
char				*ft_get_env(char *env, t_mini *mini); // of static
void				ft_pwd(t_mini *mini);
void				ft_set_env(char **argv, char **envp, t_mini *mini);
void				ft_set_array(t_mini *mini);

void				ft_lstprintold(t_list *lst);

#endif
