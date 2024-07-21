/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:13:21 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/21 16:19:13 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_value(char *__name, t_env *__env)
{
	int	len;

	while (__env)
	{
		len = ft_strlen(__env->var);
		if (!ft_strcmp(__name, __env->var))
			return (ft_strdup(__env->value));
		__env = __env->next;
	}
	return (ft_strdup(""));
}

char	*dollar_expansion(char *tmp, t_shell *shell)
{
	char	*str;
	int		count;
	int		len;

	len = ft_strlen(tmp);
	count = ft_count(tmp, '$');
	if (count % 2 == 0 || count == len || len == 1)
		return (tmp);
	else if (tmp[count] == '?')
	{
		str = ft_itoa(shell->exit_status);
		while (--count)
			str = ft_strjoin("$", str);
		return (str);
	}
	else if (count % 2 != 0)
	{
		str = set_value(tmp + count, shell->env_lst);
		while (--count)
			str = ft_strjoin("$", str);
		return (str);
	}
	return (NULL);
}

char	*limiter(int *i, char *token)
{
	int	start;
	int	end;
	int	id;

	start = *i;
	end = start + 1;
	id = 0;
	while (token[end] == '$')
		end++;
	if (token[end] == '?')
		end++;
	while (token[end] && (ft_isalnum(token[end]) || token[end] == '_'))
		end++;
	*i = end;
	return (ft_substr(token, start, *i - start));
}

char	*search_dollar(t_shell *shell, char *token)
{
	int		end;
	char	*to_join;
	char	*expanded;

	to_join = NULL;
	end = 0;
	if (!token[0])
		return (token);
	while (token[end])
	{
		if (token[end] == '$')
		{
			expanded = dollar_expansion(limiter(&end, token), shell);
			to_join = ft_strjoin(to_join, expanded);
		}
		else
		{
			to_join = ft_strjoin(to_join, char_to_string(token[end]));
			end++;
		}
	}
	return (to_join);
}

void	ft_expand(t_shell *shell)
{
	t_token	*tmp;
	char	*filter;

	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->state == DOLLAR)
		{
			filter = dollar_expansion(tmp->data, shell);
			if (!*filter)
				tmp->data = char_to_string(3);
			else
				tmp->data = filter;
		}
		else if (tmp->state == IN_DOUBLE)
			tmp->data = search_dollar(shell, tmp->data);
		tmp = tmp->next;
	}
}
