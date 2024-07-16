/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:12:54 by ezahiri           #+#    #+#             */
/*   Updated: 2024/07/16 13:49:25 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *var, char *value)
{
	t_env	*new;

	new = malloc (sizeof(t_env));
	if (!new)
		return (NULL);
	new->var = var;
	new->value = value;
	return (new);
}

void	add_env_back(t_env **head, t_env *new)
{
	t_env	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	clair_env(t_env **head)
{
	t_env	*tmp;
	t_env	*next;

	if (!head)
		return ;
	tmp = *head;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->var);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*head = NULL;
}

void	*add_env(char *var, char *value, t_env **head)
{
	t_env	*new;

	new = new_env(var, value);
	if (!new)
	{
		clair_env(head);
		return (NULL);
	}
	add_env_back(head, new);
	return (new);
}
