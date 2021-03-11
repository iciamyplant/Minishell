#ifndef MINISHELL_H
# define MINISHELL_H

/* librairy */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "../libft/libft.h"

/* global */

char	**g_envs;
pid_t	g_pid;
int		g_error;
int		g_status;

/* structures */
typedef	struct	s_sep
{
	char			*cmd_sep;
	struct s_sep	*prev;
	struct s_sep	*next;
	struct s_pip	*pipcell; //si cell est == à NULL c'est qu'il n'y a pas de pipes dans cmd_sep
}				t_sep;

typedef	struct	s_pip
{
	char			*cmd_pip;
	struct s_pip	*prev;
	struct s_pip	*next;
}				t_pip;

typedef struct		s_copy
{
	char			**args;
	char			*cmd;
	int				i;
	int				j;
}					t_copy;

typedef	struct	s_redir
{
	char		*out1; // file out pour stdout
	char		*out2; // file out pour stderr
	char		*in; // file in
	int			sstdout;
	int 		sstderr;
	int			sstdin;
	int			end;
	int			i;
}				t_redir;

/* seperation */
t_sep	*parse_sep();
void	print_list(t_sep *list);
t_sep	*add_cell(t_sep *list, char *cmd_sep, int pos);

/* pip */
void    parse_pip(t_sep *list);
void	print_pip_list(t_pip *piplist);
int		run_pipe(t_pip *pipcell, t_copy *cmdargs, int fdd, t_redir *redir);
int		status_child(pid_t	g_pid);

/* redirection */
int		redirection(char *whole_cmd, t_copy *copy, t_redir *redir);

/* cmd & arg */
char	*parsing(char *whole_cmd, t_copy *copy, t_redir *redir);
int		options(char *whole_cmd, t_copy *copy, t_redir *redir, size_t i, size_t	j);
char	*args(char *whole_cmd, t_copy *copy, size_t i, t_redir *redir);

/* protect */
int		quote_error(char c);
int		d_quote(char *whole_cmd, t_copy *copy, int j);
int		s_quote(char *whole_cmd, t_copy *copy);
int		d_quote_arg(char *whole_cmd, t_copy *copy, size_t i, int j);
int		s_quote_arg(char *whole_cmd, t_copy *copy, size_t i);
int		s_quote_redir(char *whole_cmd, t_copy *copy, int i, t_redir *redir, char *str);
int		d_quote_redir(char *whole_cmd, t_copy *copy, t_redir *redir, char *str, int std);

/* execution */
void	minishell(t_sep *list);
void	execution(t_copy *cmdarg, t_redir *redir, int pipe);
void	prompt();
int		exec(char **args, t_redir *redir, int pipe);

/* syscall */
void    call(t_copy *cmdarg);

/* env */
char    *get_env(char *env);
char    *set_env(char *env, char *new_env);
void    print_envs();
char	**get_path();
char    **realloc_envs(size_t size);
ssize_t	find_env(char *env);
size_t  get_envs_count();
int		environnement(char *whole_cmd, t_copy *copy, int arg, int i);
int		environnement_redir(char *whole_cmd, t_copy *copy, int arg, t_redir *redir);

/* builtin */
int		run_echo(char **args);
int		run_cd(char **args);
int		run_unset(char **args);
int		run_export(char **args);
void	sort_env(void);
int		run_env(void);
int		set_directory(char *path);
void	run_exit(char **args);

/* handler */
void	sigint_handler(int sign_num);

/* errors */
void	ft_error_exit(char *str, char *msg);
int		syntax_error(char *str, char c);


void	print_parsing(char **args, t_redir *redir);

#endif