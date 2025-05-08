#include "env.h"
#include "token.h"
#include "unistd.h"

t_token	*add_first_token_node(t_token **token_lst)
{
	t_token	*new_node;
	t_token	*first_node;

	new_node = ft_calloc(1, sizeof(t_token));
	if (!new_node)
		return (NULL); // NEED PROTEC
	if (!*token_lst)
	{
		*token_lst = new_node;
		new_node->next = NULL; // NEEDED ?
	}
	else
	{
		first_node = get_first_token(*token_lst);
		first_node->prev = new_node;
		new_node->next = first_node; // NEEDED ?
	}
	new_node->prev = NULL;
	return (new_node);
}

t_token	*add_last_token_node(t_token **token_lst)
{
	t_token	*new_node;
	t_token	*last_node;

	new_node = ft_calloc(1, sizeof(t_token));
	if (!new_node)
		return (NULL); // NEED PROTEC
	if (!*token_lst)
	{
		*token_lst = new_node;
		new_node->next = NULL; // NEEDED ?
	}
	else
	{
		last_node = get_last_token(*token_lst);
		last_node->next = new_node;
		new_node->prev = last_node; // NEEDED ?
	}
	new_node->next = NULL;
	return (new_node);
}

t_token	*get_first_token_node(t_token *current)
{
	if (!current)
		return (NULL);
	while (current->prev != NULL)
		current = current->prev;
	return (current);
}

t_token	*get_last_token_node(t_token *current)
{
	if (!current)
		return (NULL);
	while (current->next != NULL)
		current = current->next;
	return (current);
}

int	get_size_token_lst(t_token *current)
{
	int	size;

	size = 0;
	if (!current)
		return (NULL);
	while (current)
	{
		size++;
		current = current->next;
	}
	return (current);
}
