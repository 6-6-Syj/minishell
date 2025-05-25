#include "ast.h"
#include "libft.h"
#include "token.h"
#include "unistd.h"

int	get_args_len(t_token *token)
{
	t_token	*tmp;
	int		arg;

	tmp = token;
	arg = 0;
	while (tmp && (tmp->type == TYPE_ARG || tmp->type == TYPE_CMD
			|| tmp->type == TYPE_SPACE))
	{
		if (tmp->type == TYPE_ARG || tmp->type == TYPE_CMD)
			arg++;
		tmp = tmp->next;
	}
	return (arg);
}


t_token	*get_prev_priority_token(t_token *root_token)
{
	int	priority;
	t_token	*tmp;

	priority = root_token->priority;
	while (priority <= 5)
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
	int	priority;
	t_token	*tmp;

	priority = root_token->priority + 1;
	while (priority <= 5)
	{
		tmp = root_token->next;
		while (tmp)
		{
			if (tmp->priority == priority)
				return (tmp);
			tmp = tmp->next;
		}
		priority += 1;
	}
	return (NULL);
}

void	print_ast(t_ast *node, int depth)
{
	if (!node)
		return ;
	for (int i = 0; i < depth; i++)
		ft_printf("  ");
	if (node->type == PIPE)
	{
		ft_printf("PIPE\n");
		print_ast(node->pipe.left, depth + 1);
		print_ast(node->pipe.right, depth + 1);
	}
	else if (node->type == COMMAND)
	{
		ft_printf("COMMAND: ");
		for (int i = 0; node->command.args && node->command.args[i]; i++)
			ft_printf("%s ", node->command.args[i]);
		ft_printf("\n");
	}
}

t_token	*get_root_token(t_token **token_lst, int priority)
{
	t_token	*tmp;
	t_token	*root_token;

	root_token = NULL;
	while (priority <= 5)
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

t_ast	*create_command(t_token *token)
{
	int		i;
	int		len;
	t_ast	*new_node;
	t_token	*tmp;

	tmp = token;
	new_node = ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->type = COMMAND;
	len = get_args_len(tmp);
	new_node->command.args = ft_calloc(len + 1, sizeof(char *));
	i = 0;
	while (tmp && (tmp->type == TYPE_CMD || tmp->type == TYPE_ARG
			|| tmp->type == TYPE_SPACE))
	{
		if (tmp->type == TYPE_CMD || tmp->type == TYPE_ARG)
		{
			new_node->command.args[i] = ft_strdup(tmp->content);
			i++;
		}
		tmp = tmp->next;
	}
	new_node->command.args[i] = NULL;
	return (new_node);
}

t_ast	*create_pipe(t_ast *left, t_ast *right)
{
	t_ast	*new_node;
	
	new_node = ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->type = PIPE;
	new_node->pipe.left = left;
	new_node->pipe.right = right;
	return (new_node);
}

t_ast	*parse_token(t_token *token)
{
	t_ast	*new_node;
	t_token	*token_left;
	t_token	*token_right;
	t_ast	*node_left;
	t_ast	*node_right;

	token_left = NULL;
	token_right = NULL;
	node_left = NULL;
	node_right = NULL;
	new_node = NULL;
	if (!token)
		return (NULL);
	if (token->type == TYPE_PIPE)
	{
		token_left = get_prev_priority_token(token);
		token_right = get_next_priority_token(token);
		node_left = parse_token(token_left);
		node_right = parse_token(token_right);
		new_node = create_pipe(node_left, node_right);
		return (new_node);
	}
	if (token->type == TYPE_CMD)
		return (create_command(token));
	return (NULL);
}


int	init_ast(t_ast **ast_lst, t_token **token_lst)
{
	t_token	*root_token;

	if (!token_lst || !*token_lst)
		return (1);
	root_token = get_root_token(token_lst, 0);
	if (!root_token)
		return (1);
	*ast_lst = parse_token(root_token);
	return (0);
}

