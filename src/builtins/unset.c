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

static int	ft_unset(t_env **head, char *key_to_remove)
{
	t_env	*curr;
	t_env	*prev;

	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (curr-> key && !ft_strcmp(curr->key, key_to_remove))
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
	/* TODO: ERROR if unset a readonly var
	f.e.: CHECK ACCESS
	bash: unset: VAR: cannot unset: readonly variable */
	return (0);
}

int	handle_unset(t_env **env_lst, char *input)
{
	char	**args;
	int		i;
	int		res;

	res = 0;
	args = ft_split(input, ' ');
	if (args && args[1])
		res = ft_unset(env_lst, args[1]);
	i = 0;
	while (args && args[i])
		free(args[i++]);
	free(args);
	return (res);
}
