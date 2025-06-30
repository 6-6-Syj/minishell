#include "data.h"
#include "libft.h"
#include "token.h"
#include "unistd.h"

int	remove_node(t_token *node, t_data *data)
{
	t_token	*prev;
	t_token	*next;

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
		next->prev = data->token;
	}
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	return (0);
}

int	set_command_type(t_token **token_lst)
{
	t_token	*token_node;
	t_token	*tmp;

	token_node = *token_lst;
	while (token_node)
	{
		tmp = token_node->next;
		if (token_node->type == WORD)
		{
			token_node->type = CMD;
			while (tmp && tmp->type != PIPE)
			{
				if (tmp->type == WORD)
					tmp->type = ARG;
				tmp = tmp->next;
			}
		}
		token_node = token_node->next;
	}
	return (0);
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

void	set_token_priority(t_token **token_lst) // TODO: refacto
{
	t_token	*token_node;

	token_node = *token_lst;
	while (token_node)
	{
		if (token_node->type == PIPE)
			token_node->priority = 1;
		else if (token_node->type == CMD)
			token_node->priority = 2;
		else
			token_node->priority = -1;
		token_node = token_node->next;
	}
}
