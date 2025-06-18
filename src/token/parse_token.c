#include "data.h"
#include "libft.h"
#include "token.h"
#include "unistd.h"

int	remove_node(t_token *node)
{
	t_token	*prev;
	t_token	*next;

	prev = node->prev;
	next = node->next;
	if (!node)
		return (0);
	free(node);
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	return (0);
}

// int	parse_logic_node(t_token *node)
// {
// 	if (!node || !node->prev || !node->next)
// 		return (-1);
// 	if (node->prev->type != TYPE_SPACE || node->next->type != TYPE_SPACE)
// 		return (-1);
// 	return (0);
// }

// int	parse_command_node(t_token *node)
// {
// 	char	*buff;
// 	t_token	*tmp;

// 	if (!node)
// 		return (-1);
// 	tmp = node->next;
// 	while (tmp && tmp->type != TYPE_AND && tmp->type != TYPE_OR
// && tmp->type != TYPE_PIPE) // TODO: handle parenthesis
// 	{
// 		if (tmp->type == TYPE_ARG)
// 		{
// 			buff = ft_strjoin(node.)
// 		}
// 		tmp = tmp->next;
// 	}
// }

// int	parse_token_node(t_token *token_node)
// {
// 	int	status;

// 	if (token_node->type == TYPE_AND || token_node->type == TYPE_OR)
// 		status = parse_logic_node(token_node);
// 	if (token_node->type == TYPE_CMD)
// 		status = parse_command_node(token_node);
// 	if (token_node->type == TYPE_QUOTE_S)
// 		status = parse_quote_s_node(token_node);
// 	if (token_node->type == TYPE_QUOTE_D)
// 		status = parse_quote_d_node(token_node);
// }

int	set_command_type(t_token **token_lst)
{
	t_token	*token_node;
	t_token	*tmp;

	token_node = *token_lst;
	while (token_node)
	{
		tmp = token_node->next;
		if (token_node->type == TYPE_WORD)
		{
			token_node->type = TYPE_CMD;
			while (tmp && !(tmp->type & TYPE_OPERATOR))
			{
				if (tmp->type == TYPE_WORD)
					tmp->type = TYPE_ARG;
				tmp = tmp->next;
			}
		}
		token_node = token_node->next;
	}
	return (0);
}

int	set_file_type(t_token **token_lst)
{
	t_token	*token_node;

	token_node = *token_lst;
	while (token_node)
	{
		if (token_node->type & TYPE_REDIR && token_node->next)
		{
			token_node->next->type = TYPE_FILE;
		}
		token_node = token_node->next;
	}
	return (0);
}

int	parse_command(t_token **token_lst) ///////////
{
	t_token *token_node;
	t_token *tmp;
	char *buff;
	char *buff2;

	token_node = *token_lst;
	while (token_node)
	{
		tmp = token_node->next;
		while (token_node->type == TYPE_CMD && tmp
			&& !(tmp->type & TYPE_OPERATOR))
		{
			if (tmp->type == TYPE_ARG)
			{
				buff = ft_strjoin(" ", tmp->content);
				buff2 = ft_strjoin(token_node->content, buff);
				free(buff);

				remove_node(tmp);
				free(token_node->content);
				token_node->content = ft_strdup(buff2);
				free(buff2);
			}
			tmp = tmp->next;
		}
		token_node = token_node->next;
	}
	return (0);
}

int	parse_token_lst(t_token **token_lst)
{
	set_file_type(token_lst);
	set_command_type(token_lst);
	// concatenate command + args;
	//
	parse_command(token_lst);
	return (0);
}
