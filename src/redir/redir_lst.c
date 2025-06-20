#include "redir.h"
#include "unistd.h"



t_redir	*get_first_redir_node(t_redir *current)
{
	if (!current)
		return (NULL);
	while (current->prev != NULL)
		current = current->prev;
	return (current);
}

t_redir	*get_last_redir_node(t_redir *current)
{
	if (!current)
		return (NULL);
	while (current->next != NULL)
		current = current->next;
	return (current);
}

t_redir	*add_redir_node(t_redir **redir_lst)
{
	t_redir	*new_node;
	t_redir	*last_node;

	new_node = ft_calloc(1, sizeof(t_redir));
	if (!new_node)
		return (NULL); // NEED PROTEC
	if (!*redir_lst)
	{
		*redir_lst = new_node;
		new_node->next = NULL; // NEEDED ?
	}
	else
	{
		last_node = get_last_redir_node(*redir_lst);
		last_node->next = new_node;
		new_node->prev = last_node; // NEEDED ?
	}
	new_node->next = NULL;
	return (new_node);
}
