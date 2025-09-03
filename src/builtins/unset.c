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
#include "env.h"
#include "libft.h"

static void	ft_unset(t_command *cmd, int *i, t_env **head)
{
	t_env	*curr;
	t_env	*prev;

	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (curr->key && !ft_strcmp(curr->key, cmd->args[*i]))
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			free(curr->key);
			if (curr->value)
				free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	handle_unset(t_command *cmd, t_env **env_lst, t_data *data)
{
	int	i;

	i = 1;
	while (cmd && cmd->args[i])
	{
		ft_unset(cmd, &i, env_lst);
		i++;
	}
	update_env_tab(data);
	return (0);
}
