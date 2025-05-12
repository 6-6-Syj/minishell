#include <stdlib.h>
#include "token.h"

void	free_token_node(t_token *token_node)
{
		if (token_node->content)
			free(token_node->content);
		free(token_node);
}

void	free_token_lst(t_token **token_lst)
{
	t_token	*current;
	t_token	*tmp;

	current = token_lst;
	while (current)
	{
		tmp = current->next;
		free_token_node(current);
		current = tmp;
	}
}
