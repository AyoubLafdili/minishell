/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:13:58 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/09 19:04:50 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
		printf ("%s\n", pwd);
	else if (shell->old_pwd)
		printf ("%s\n", shell->old_pwd);
	else
	{
		perror("pwd");
		shell->exit_status = 1;
		free(pwd);
		return ;
	}
	free(pwd);
}
