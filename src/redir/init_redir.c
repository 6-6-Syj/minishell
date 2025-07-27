#include "ast.h"
#include "data.h"
#include "print.h"
#include "redir.h"
#include "token.h"
#include "unistd.h"

t_token	*get_first_redir(t_token **root_token)
{
	t_token	*token_node;

	if (!*root_token)
		return (NULL);
	token_node = *root_token;
	while (token_node->prev && token_node->prev->type != PIPE)
		token_node = token_node->prev;
	while (token_node && token_node->type != PIPE)
	{
		if (token_node->type & REDIR)
			return (token_node);
		token_node = token_node->next;
	}
	return (NULL);
}

t_token	*get_next_redir(t_token **root_token)
{
	t_token	*token_node;

	if (!*root_token || !(*root_token)->next)
		return (NULL);
	token_node = (*root_token)->next;
	while (token_node && token_node->type != PIPE)
	{
		if (token_node->type & REDIR)
			return (token_node);
		token_node = token_node->next;
	}
	return (NULL);
}

char	*get_redir_delimiter(t_token *token_node)
{
	while (token_node && token_node->type != PIPE)
	{
		if (token_node->type == REDIR_TARGET)
			return (token_node->content);
		token_node = token_node->next;
	}
	return (NULL);
}

int	set_redir_node(t_redir *redir_node, t_token *token_node, t_data *data)
{
	(void)data;
	if (!token_node || !token_node->next)
		return (-1);
	redir_node->type = token_node->type;
	if (token_node->type == HERE_DOC)
	{
		redir_node->delimiter = ft_strjoin(get_redir_delimiter(token_node),
				"\n");
		if (!redir_node->delimiter)
			return (-1);
		set_here_doc(&redir_node);
	}
	else if (token_node->type & REDIR)
	{
		redir_node->filename = ft_strdup(token_node->next->content);
		if (!redir_node->filename)
			return (-1);
	}
	return (0);
}

void	init_redir(t_token *token_node, t_redir **redir_lst, t_data *data)
{
	t_redir	*new_redir;

	new_redir = *redir_lst;
	token_node = get_first_redir(&token_node);
	while (token_node)
	{
		new_redir = add_redir_node(redir_lst);
		if (!new_redir)
			return ;
		if (set_redir_node(new_redir, token_node, data) == -1)
			return ;
		token_node = get_next_redir(&token_node);
	}
}

// void	init_redir_no_cmd(t_token **token_lst, t_data *data)
// {
// 	t_token *current;

// 	current = *token_lst;
// 	while (current)
// 	{
// 		if (current->type & REDIR)

// 		current = current->next;
// 	}
// }
