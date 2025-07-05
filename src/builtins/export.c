/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:22:44 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/08 17:26:21 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "print.h"

static bool	search_key_update_value(t_data *data, t_env **head, char *key,
		char *value)
{
	t_env	*curr;

	curr = *head;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			if (value)
			{
				free(curr->value);
				curr->value = ft_strdup(value);
				if (!curr->value)
					malloc_fail(data);
			}
			curr->print_env = true;
			curr->print_exp = true;
			return (true);
		}
		curr = curr->next;
	}
	return (false);
}

static void	free_and_exit(t_data *data, t_env *new)
{
	free(new->key);
	free(new);
	malloc_fail(data);
}

static bool	add_key(t_data *data, t_env **head, char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		malloc_fail(data);
	new->key = ft_strdup(key);
	if (!new->key)
	{
		free(new);
		malloc_fail(data);
	}
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
			free_and_exit(data, new);
	}
	else
		new->value = NULL;
	new->next = *head;
	*head = new;
	return (true);
}

bool	is_special_char(char c)
{
	if (c > '!' && c < '*')
		return (true);
	if (c >= ':' && c <= '?' && c != '=' && c != '@' && c != '#' && c != '^')
		return (true);
	if (c >= '[' && c <= ']')
		return (true);
	if (c > '{' && c < '}')
		return (true);
	if (c == '|' || c == '"' || c == '$' || c == '&' || c == ';')
		return (true);
	if (c == '<' || c == '>' || c == '~' || c == '`')
		return (true);
	return (false);
}

static bool	got_special_char(char *key)
{
	int	i;

	i = 1;
	while (key && key[i])
	{
		if (is_special_char(key[i]))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
			ft_putchar_fd(key[i], STDERR_FILENO);
			ft_putstr_fd("'\n", STDERR_FILENO);
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	is_key_valid(char *key)
{
	int	i;

	if (!key || (key[0] != '_' && !ft_isalpha(key[0])))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(key, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (false);
	}
	i = 0;
	while (key[i])
	{
		if (key[i] == '-' || key[i] == '!' || key[i] == '@' || key[i] == '#'
			|| key[i] == '*' || key[i] == '^' || key[i] == '{' || key[i] == '}'
			|| (key[i] == '+' && key[i + 1] != '=' ) || key[i] == '.') // builtins bash
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(key, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (false);
		}
		i++;
	}
	return (true);
}

static int	ft_export(t_env **env_lst, t_data *data, char *args)
{
	char	*key;
	char	*value;
	char	*equal;

	key = args;
	value = NULL;
	if (!is_key_valid(key))
		return (1);
	if (got_special_char(key))
		return (2);
	equal = ft_strchr(key, '=');
	if (equal)
	{
		*equal = '\0';
		value = equal + 1;
	}
	if (search_key_update_value(data, env_lst, key, value) || add_key(data,
			env_lst, key, value))
	{
		update_env_tab(data);
		return (NO_ERROR);
	}
	return (1);
}

// TODO: if variable got a value "with spaces",
// there are problems. (PARSING EXPORT)
// It exports at each ' ';
// See raw 110
int	handle_export(t_command *cmd, t_env **env_lst, t_data *data)
{
	int	i;

	i = 1;
	if (cmd && !cmd->args[1])
		data->err = print_export(*env_lst, data);
	else
	{
		while (cmd->args[i])
		{
			data->err = ft_export(env_lst, data, cmd->args[i]);
			i++;
		}
	}
	return (data->err);
}
