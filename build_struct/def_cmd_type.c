/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_cmd_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:38:30 by alafdili          #+#    #+#             */
/*   Updated: 2024/08/09 19:14:01 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_type_def(t_shell *shell)
{
	char	**builtins;
	t_cmd	*cmd;
	int		i;

	builtins = ft_split("cd pwd export unset env echo exit", ' ');
	cmd = shell->cmd;
	while (cmd)
	{
		i = 0;
		while (cmd->cmd && builtins[i])
		{
			cmd->type = false;
			if (!ft_strcmp(cmd->cmd, builtins[i]))
			{
				cmd->type = true;
				break ;
			}
			i++;
		}
		cmd = cmd->next;
	}
}
