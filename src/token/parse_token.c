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
// 	if (node->prev->type != SPACE || node->next->type != SPACE)
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
// 	while (tmp && tmp->type != AND && tmp->type != OR
// && tmp->type != PIPE) // TODO: handle parenthesis
// 	{
// 		if (tmp->type == ARG)
// 		{
// 			buff = ft_strjoin(node.)
// 		}
// 		tmp = tmp->next;
// 	}
// }

// int	parse_token_node(t_token *token_node)
// {
// 	int	status;

// 	if (token_node->type == AND || token_node->type == OR)
// 		status = parse_logic_node(token_node);
// 	if (token_node->type == CMD)
// 		status = parse_command_node(token_node);
// 	if (token_node->type == QUOTE_S)
// 		status = parse_quote_s_node(token_node);
// 	if (token_node->type == QUOTE_D)
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

int	set_file_type(t_token **token_lst)
{
	t_token	*token_node;

	token_node = *token_lst;
	while (token_node)
	{
		if (token_node->type & REDIR && token_node->next)
		{
			token_node->next->type = REDIR_TARGET;
		}
		token_node = token_node->next;
	}
	return (0);
}

int	remove_space(t_token **token_lst)
{
	t_token	*token_node;
	t_token	*tmp;

	token_node = *token_lst;
	while (token_node)
	{
		tmp = token_node->next;
		if (token_node->type == SPACE)
			remove_node(token_node);
		token_node = tmp;
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
		while (token_node->type == CMD && tmp
			&& tmp->type != PIPE)
		{
			if (tmp->type == ARG)
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
		token_node = token_node->next;
	}
}

int	parse_token_lst(t_token **token_lst)
{
	remove_space(token_lst);
	set_file_type(token_lst);
	set_command_type(token_lst);
	set_token_priority(token_lst);
	// concatenate command + args;
	//
	// parse_command(token_lst);
	return (0);
}
