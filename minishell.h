/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 17:20:58 by salbregh      #+#    #+#                 */
/*   Updated: 2021/01/28 17:11:32 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <stdio.h> // delete after
# include <stdlib.h>
# include <sys/syslimits.h> // not sure if allowed?
# include <fcntl.h>
# include <signal.h>


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

// Struct only used for redirection 
typedef struct		s_redir
{
	char			*file;
	char			*m_files;
	char			*error;
	int				i;
	int				d;
	int 			redirinput;
	int 			j;
	int 			fd;
	int				alpha;
}					t_redir;

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
	char			*notbuiltin[23]; // ls mkdir touch cat
	int				stdout;
	int				stderr;
	int				numb_cmds; // Command counter new struct
	char 			*cmd_part;
	int				type_end;
	int				stdin;
	int				exit;
	int				singlequote;
}					t_mini;

typedef struct		s_piper
{
	int				check;
	char			*write_side;
	char			*read_side;
	int				fd[2]; // fd[0] - read fd[1] - write made by pipe(fd);
}					t_piper;

/* LIST FUNCTIONS */
t_list				*ft_lstnew(void *var1, void *var2);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstadd_back_new(t_base **ptr, t_base *new); // new replace this one or old one
void				ft_lstprint(t_list *lst, t_mini *mini);
void				ft_lstclear(t_list **lst);
int  				ft_split_into_tlist(t_mini *mini, char *line);
void				ft_lstprintold(t_list *lst);

/* BUILTIN FUNCTION */
int 			  	ft_echo(t_base *ptr, t_mini *mini);
int					ft_export(t_base *ptr, t_mini *mini);
int					ft_unset(t_mini *mini, char *unset);
void				ft_cd(t_base *ptr, t_mini *mini); // new
void				ft_pwd(t_mini *mini);

/* PARSER FUNCTIONS */
void				parse_input_string(char *line, t_mini *mini, char **envp);


int					ft_start_parsing(char *line, t_mini *mini, char **envp); // new
// int				ft_echo(char *string, t_mini *mini, t_piper *piper);
// void				ft_putstr(char *s);
char				*ft_check_dolla_quotes(char *line, t_mini *mini, int i);
int					unvalid_identifier(char *error, t_mini *mini);
int 				ft_strchr_numb(char *line, char c, int i);
int					ft_strrchr_numb(char *line, char c, int i);
int  				numb_char(char *line, char c);

// int				ft_execve(t_mini *mini, char **envp, t_piper *piper);
void				exec_cmds(t_base *ptr, char **envp, t_mini *mini);

int					look_for_non_builtin(t_base *ptr);

// int					ft_redir(t_mini *mini, int d);


int  				ft_split_into_tlist(t_mini *mini, char *line);
t_list				*ft_lstnew(void *var1, void *var2);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstprint(t_list *lst, t_mini *mini);
// int					ft_builtin(t_mini *mini, char *command, char *more, char **envp);
int					ft_execve(t_mini *mini, char **envp);
void				ft_lstclear(t_list **lst);
int					ft_redir(t_mini *mini, char **envp);
int					ft_parse_input(char *command, char *more, t_mini *mini, char **envp);
void				ft_printf_exit_status(t_mini *mini);
char				*ft_string_insert(char *string, int i, char *middle);
void 				ft_close_fds(t_mini *mini);
void				ft_exit(t_mini *mini, char *line, int exitstatus);
char				*ft_strjoin_three(char *start, char *newvar, char *end);
void				handle_sigint(int sig);
void				ft_signals(t_mini *mini, char *line, int i);
void				ft_add_env(char *env, char *path, t_mini *mini); // or static
char				*ft_get_env(char *env, t_mini *mini); // of static

void				ft_set_env(char **argv, char **envp, t_mini *mini);
void				ft_set_array(t_mini *mini);


#endif
