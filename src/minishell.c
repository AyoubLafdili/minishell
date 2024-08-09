/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:20:24 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/09 18:52:53 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__ctrl_d(t_shell *shell)
{
	close(shell->input[0]);
	close_fd(shell->tokens, NULL);
	stock_addr(NULL, 0);
	ft_malloc(0, 0);
	printf("\x1b[FMinishell$ exit\n");
	exit(shell->exit_status);
}

void	interpreter(t_shell *shell, char *line)
{
	if (catch_signal(0, GET) == SIGINT)
	{
		shell->exit_status = 1;
		catch_signal(0, SET);
	}
	if (!*line)
		return ;
	add_history(line);
	tokenizer(line, shell);
	parser(shell, shell->tokens);
	expander(shell);
	get_pipeline(shell);
	executer(shell);
}

void	mini_shell(t_shell *shell)
{
	char	*line;

	shell->input[0] = dup(0);
	while (1)
	{
		shell->stoped = 0;
		line = readline("Minishell$ ");
		stock_addr(line, 2);
		if (!line && catch_signal(0, GET) == SIGINT)
		{
			dup2(shell->input[0], 0);
			shell->exit_status = 1;
			catch_signal(0, SET);
			continue ;
		}
		if (!line)
			__ctrl_d(shell);
		interpreter(shell, line);
		ft_malloc(0, 0);
		shell->tokens = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	ft_signal();
	ft_memset(&shell, 0, sizeof(t_shell));
	shell.input[0] = -1;
	shell.input[1] = -1;
	shell.env = env;
	inisailise_env(env, &shell);
	mini_shell(&shell);
}
