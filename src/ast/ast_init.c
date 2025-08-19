#include "ast.h"
#include "libft.h"
#include "print.h"
#include "redir.h"
#include "token.h"
#include "unistd.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

// TODO: Replace return by exit_error

bool	is_command(t_token *token_node)
{
	while (token_node)
	{
		if (token_node->type == CMD)
			return (false);
		token_node = token_node->next;
	}
	return (true);
}

int	get_args_len(t_token *token)
{
	t_token	*tmp;
	int		arg;

	tmp = token;
	arg = 0;
	while (tmp && (tmp->type == ARG || tmp->type == CMD || tmp->type == SPACE))
	{
		if (tmp->type == ARG || tmp->type == CMD)
			arg++;
		tmp = tmp->next;
	}
	return (arg);
}

t_token	*get_prev_priority_token(t_token *root_token)
{
	int		priority;
	t_token	*tmp;

	priority = root_token->priority;
	while (priority <= 2)
	{
		tmp = root_token->prev;
		while (tmp)
		{
			if (tmp->priority == priority)
				return (tmp);
			tmp = tmp->prev;
		}
		priority++;
	}
	return (NULL);
}

t_token	*get_next_priority_token(t_token *root_token)
{
	int		priority;
	t_token	*tmp;

	priority = root_token->priority + 1;
	while (priority <= 2)
	{
		tmp = root_token->next;
		while (tmp)
		{
			if (tmp->priority == priority)
				return (tmp);
			tmp = tmp->next;
		}
		priority++;
	}
	return (NULL);
}

t_token	*get_root_token(t_token **token_lst, int priority)
{
	t_token	*tmp;
	t_token	*root_token;

	root_token = NULL;
	while (priority <= 2)
	{
		tmp = *token_lst;
		while (tmp)
		{
			if (tmp->priority == priority)
				root_token = tmp;
			tmp = tmp->next;
		}
		if (root_token)
			return (root_token);
		priority++;
	}
	return (root_token);
}

t_ast	*create_command_node(t_token *token, t_data *data)
{
	int		i;
	int		len;
	t_ast	*new_node;
	t_token	*tmp;

	tmp = token;
	new_node = ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->command.fd_in = -1;
	new_node->command.fd_out = -1;
	new_node->type = CMD;
	len = get_args_len(tmp);
	new_node->command.args = ft_calloc(len + 2, sizeof(char *));
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CMD || tmp->type == ARG)
			new_node->command.args[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
		if (!tmp)
			new_node->command.args[i] = NULL;
	}
	init_redir(token, &new_node->command.redir, data);
	return (new_node);
}

t_ast	*create_pipe_node(t_token *token, t_data *data)
{
	t_ast	*new_node;
	t_token	*token_left;
	t_token	*token_right;

	token_left = get_prev_priority_token(token);
	token_right = get_next_priority_token(token);
	new_node = ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->pipe.left = parse_token(token_left, data);   // TODO: secure
	new_node->pipe.right = parse_token(token_right, data); // TODO: secure
	new_node->type = PIPE;
	return (new_node);
}

t_ast	*create_logic_node(t_token *token, t_data *data)
{
	t_ast	*new_node;
	t_token	*token_left;
	t_token	*token_right;

	token_left = get_prev_priority_token(token);
	token_right = get_next_priority_token(token);
	new_node = ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->logic.left = parse_token(token_left, data);
	new_node->logic.right = parse_token(token_right, data);
	if (ft_strcmp(token->content, "&&") == 0)
		new_node->type = AND;
	if (ft_strcmp(token->content, "||") == 0)
		new_node->type = OR;
	return (new_node);
}

t_ast	*parse_token(t_token *token, t_data *data)
{
	if (!token)
		return (NULL);
	if (token->type == PIPE)
		return (create_pipe_node(token, data));
	if (token->type == CMD)
		return (create_command_node(token, data));
	else if (token->type & REDIR)
		return (create_command_node(token, data));
	return (NULL);
}

int	init_ast(t_ast **ast_lst, t_token **token_lst, t_data *data)
{
	t_token	*root_token;

	root_token = get_root_token(token_lst, 0);
	if (!root_token) // handle special case here ? (no command)
		return (1);
	*ast_lst = parse_token(root_token, data);
	return (0);
}