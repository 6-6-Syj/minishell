/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:17:38 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/05 20:15:33 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_unset(t_command *cmd, t_env **head)
{
	t_env	*curr;
	t_env	*prev;

	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (curr->key && !ft_strcmp(curr->key, cmd->args[1]))
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

int	handle_unset(t_command *cmd, t_env **env_lst, t_data *data)
{
	int		res;

	res = 0;
	if (cmd->args && cmd->args[1])
		res = ft_unset(cmd, env_lst);
	update_env_tab(data);
	return (res);
}
