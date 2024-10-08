/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:13:21 by ezahiri           #+#    #+#             */
/*   Updated: 2024/08/13 17:17:50 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_shell *shell)
{
	char	*to_check;
	t_token	*tmp;

	tmp = shell->tokens;
	if (shell->stoped)
		return ;
	while (tmp)
	{
		if (tmp->state == DOLLAR)
		{
			to_check = dollar_expansion(tmp->data.content, shell);
			if (!to_check || !*to_check)
				tmp->data.content = NULL;
			else
				tmp->data.content = to_check;
		}
		else if (tmp->state == IN_DOUBLE)
			tmp->data.content = search_dollar(shell, tmp->data.content);
		else if (tmp->type == HERE && !check_is_double(tmp->next))
			heredoc_expansion(shell, &tmp->data.fd);
		tmp = tmp->next;
	}
}
