/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:26:31 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/19 17:00:56 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_argument(char *arg)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	arg = ft_strtrim(arg, " ");
	if (*arg == '-' || *arg == '+')
		sign = 1 - 2 * (*(arg++) == '-');
	if (*arg == '\0')
		return (false);
	while (arg[i])
		if (!ft_isdigit(arg[i++]))
			return (false);
	while (*arg == '0')
		arg++;
	if ((ft_strncmp(arg, "9223372036854775807", 19) > 0 && sign == 1)
		|| ft_strlen(arg) > 19)
		return (false);
	if ((ft_strncmp(arg, "9223372036854775808", 19) > 0 && sign == -1)
		|| ft_strlen(arg) > 19)
		return (false);
	return (true);
}

void	ft_exit(t_shell *shell, t_cmd *cmd)
{
	int		len;

	len = 1;
	while (cmd->args[len])
		len++;
	if (child_exist(0, GET) == false)
		ft_putendl_fd("exit", 1);
	if (len == 1)
		exit(shell->exit_status);
	if (check_argument(cmd->args[1]) == true && len > 2)
	{
		_p_err(NULL, (char *[3]){TMA, "exit", ""}, -1);
		shell->exit_status = 1;
		return ;
	}
	else if (check_argument(cmd->args[1]) == false)
	{
		_p_err(NULL, (char *[3]){NAR, "exit", ""}, -1);
		exit(255);
	}
	else if (check_argument(cmd->args[1]) == true)
		exit(ft_atoi(cmd->args[1]));
}
