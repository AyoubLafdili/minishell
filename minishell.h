/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 07:48:29 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/16 16:09:32 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <stdbool.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define AMBIGOUS "ambiguous redirect"
# define CNF "command not found"
# define ISDIR "is a directory"
# define NAVI ": not a valid identifier"
# define NAR "numeric argument required"
# define TMA "too many arguments"
# define SUCCESS 0
# define FAIL 1

# define SET 1
# define GET 0

typedef enum e_type
{
	IN,
	OUT,
	HERE,
	APPEND,
	ERROR,
	WORD,
	PIPE
}			t_type;

typedef enum e_state
{
	DEFAULT,
	IN_SINGALE,
	IN_DOUBLE,
	DOLLAR
}			t_state;

typedef enum e_joinble
{
	JOINBLE,
	NON_JOINBLE
}			t_join;

typedef struct s_token_data
{
	int		fd;
	char	*origin;
	char	*content;
}	t_data;

typedef struct s_token
{
	t_join			join;
	t_state			state;
	t_type			type;
	t_data			data;
	struct s_token	*next;
}				t_token;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_redir
{
	int				fd;	
	char			*file;
	t_type			type;
	struct s_redir	*next;
}				t_redir;

typedef struct s_cmd
{
	bool			type;
	char			*cmd;
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_shell
{
	int		input;
	int		stoped;
	int		exit_status;
	char	*cpy_pwd;
	char	*old_pwd;
	char	**env;
	t_env	*env_lst;
	t_token	*tokens;
	t_cmd	*cmd;
}				t_shell;

/******** Tokenization/parsing + opening heredoc functions *********/

int		is_spec(char c);
t_join	is_joinble(char c);
void	tokenizer(char *line, t_shell *shell);
void	parser(t_shell *shell, t_token *tokens);
bool	ft_here_doc(t_shell *shell, t_token *head);
void	word_delimiter(char *token, int *i, t_token **head, t_state state);
int		quote_delimiter(char *token, int *i, t_shell *shell, t_state state);
void	dollar_delimiter(char *token, int *i, t_token **head, t_state state);
void	opertor_delimiter(char *token, int *i, t_token **head, t_state state);

/********************** Execution functions ************************/

void	executer(t_shell *shell);
int		researcher(char *s, char c);
void	close_rdir_fds(t_redir *head);
char	*check_cmd(char *path, char *cmd);
char	*check_cmd(char *path, char *cmd);
void	close_fd(t_token *token, t_cmd *head);
char	*set_value(char *__name, t_env *__env);
bool	check_executable(t_cmd *head, t_cmd *cmd);
bool	redirection_check(t_cmd *cmd, t_redir *lst);
void	get_exit_status(t_shell *shell, pid_t last_cmd);
int		builtin_exec(t_shell *shell, t_cmd *cmd, int *ends);
void	apply_redirs(t_shell *shell, t_redir *head, int *ends, t_cmd *last);
void	value_non_joinlble(char *name, char *value, t_shell *shell, int flag);

/***************** Building execution struct functions *************/

void	cmd_type_def(t_shell *shell);
void	get_pipeline(t_shell *shell);
void	cmd_add_back(t_cmd **lst, t_cmd *new);
t_cmd	*create_cmd(char *to_join, t_redir *redir);
void	join_export_word(char **to_join, t_token **start);
void	get_cmd_part(t_token **head, t_redir **redir, char **args);
void	check_and_join(char **filename, t_token *token, bool empty_str);

/********************** Expanding functions ************************/

void	expander(t_shell *shell);
char	*limiter(int *i, char *token);
bool	check_is_double(t_token *tmp);
char	*search_dollar(t_shell *shell, char *token);
char	*dollar_expansion(char *tmp, t_shell *shell);
void	heredoc_expansion(t_shell *shell, int *old_fd);

/********************** built-in functions *************************/

void	ft_env(t_shell *shell);
void	ft_pwd(t_shell *shell);
void	ft_cd(t_shell *shell, t_cmd *cmd);
void	ft_exit(t_shell *shell, t_cmd *cmd);
void	ft_echo(t_shell *shell, t_cmd *cmd);
void	ft_unset(t_shell *shell, t_cmd *cmd);
void	ft_export(t_shell *shell, t_cmd *cmd);

/********************** env functions ******************************/

char	*dup_env(char *s);
int		env_size(t_env *lst);
char	*join_env(char *s1, char *s2);
bool	exist_env(char *name, t_env *env);
void	set_env(t_shell *shell, char *arg);
char	*get_env_key(t_env *env, char *name);
void	print_env(t_shell *shell, t_env *env);
void	initialize_env(char **env, t_shell *shell);
void	*add_env(char *var, char *value, t_env **head);
char	*subenv(char const *s, unsigned int start, size_t len);

/********************** PRINT/CHECK Error functions ****************/

void	clean_up(t_shell *shell);
bool	check_ambiguous(t_token *token);
void	display_syntax_error(t_shell *shell);
void	ft_export_error(char *arg, t_shell *shell);
void	close_and_perror(t_shell *shell, int *to_close, int exit);
void	_p_err(t_cmd *head, char **err_msg, int exit_code);
void	syntax_error_check(t_shell *shell, t_token *limiter, int flag);

/********************** STRING utils functions *********************/

bool	is_valid(char *arg);
char	*char_to_string(char c);
int		ft_count(char *str, char c);
char	*space_tab_trimer(char *str);
char	*remove_char(char *str, char c);
void	join_word(char **to_join, t_token **start);
void	space_to_127(t_token *token, t_state check_with);

/********************** Signals functions **************************/

void	ft_signal(void);
int		catch_signal(int s, bool set_or_get);
int		child_exist(int is_exist, bool mode);

/********************** Lists functions ****************************/

int		cmd_lst_size(t_cmd *lst);
t_cmd	*new_cmd(char *cmd, t_redir *redir, char **args);
void	add_redir(t_redir **lst, char *file, t_type type, int fd);
void	add_lst(char *content, t_token **lst, t_state state, t_join join);

#endif
