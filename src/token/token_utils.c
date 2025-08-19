#include "minishell.h"

int	get_token_len(char *token)
{
	int	i;

	i = 1;
	while (token[i])
	{
		if (token[0] == '|' && token[i] != '|')
			return (i);
		else if (token[0] == '<' && token[i] != '<')
			return (i);
		else if (token[0] == '>' && token[i] != '>')
			return (i);
		else if (is_operator(token[0]) && !is_operator(token[i]))
			return (i);
		else if (token[0] == '\'' && token[i] == '\'')
			return (i + 1);
		else if (token[0] == '\"' && token[i] == '\"')
			return (i + 1);
		else if (is_space(token[0]) && !is_space(token[i]))
			return (i);
		else if (is_part_of_word(token[0]) && !is_part_of_word(token[i]))
			return (i);
		i++;
	}
	return (i);
}

void	set_token_priority(t_token **token_lst) // TODO: refacto
{
	t_token *token_node;

	token_node = *token_lst;
	while (token_node)
	{
		if (token_node->type == PIPE)
			token_node->priority = 0;
		else if (token_node->type == CMD)
			token_node->priority = 1;
		else if (token_node->type & REDIR)
			token_node->priority = 2;
		else
			token_node->priority = -1;
		token_node = token_node->next;
	}
}

void	join_word(t_token **token_lst, t_data *data)
{
	t_token	*current;
	char	*buff;

	(void)data;
	current = *token_lst;
	while (current && current->next)
	{
		if (current->type == current->next->type)
		{
			buff = ft_strjoin(current->content, current->next->content);
			free(current->content);
			current->content = buff;
			remove_node(current->next, data);
		}
		else
			current = current->next;
	}
}

int	remove_space(t_token **token_lst, t_data *data)
{
	t_token	*token_node;
	t_token	*tmp;

	token_node = *token_lst;
	while (token_node)
	{
		tmp = token_node->next;
		if (token_node->type == SPACE)
			remove_node(token_node, data);
		token_node = tmp;
	}
	return (0);
}

int	remove_node(t_token *node, t_data *data)
{
	t_token *prev;
	t_token *next;

	prev = node->prev;
	next = node->next;
	if (!node)
		return (0);
	if (node->content)
		free(node->content);
	free(node);
	if (!prev)
	{
		data->token = next;
		if (next)
			next->prev = data->token;
	}
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	return (0);
}
