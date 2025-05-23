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

t_token	*get_next_executable(t_token *token) // TMP
{
	t_token *next;

	next = token->next;
	while (next)
	{
		if (next->type == TYPE_CMD || next->type == TYPE_PIPE)
			return (next);
		next = next->next;
	}
	return (NULL);
}

t_token	*get_prev_executable(t_token *token) // TMP
{
	t_token *prev;

	prev = token->prev;
	while (prev)
	{
		if (prev->type == TYPE_CMD || prev->type == TYPE_PIPE)
			return (prev);
		prev = prev->prev;
	}
	return (NULL);
}
t_token	*get_last_prioritary_before(t_token *start, int priority)
{
	t_token	*tmp;
	t_token	*last;

	tmp = start;
	last = NULL;
	while (tmp)
	{
		if (tmp->priority == priority)
			last = tmp;
		tmp = tmp->prev;
	}
	return (last);
}

t_token	*get_last_prioritary_after(t_token *start, int priority)
{
	t_token	*tmp;
	t_token	*last;

	tmp = start;
	last = NULL;
	while (tmp)
	{
		if (tmp->priority == priority)
			last = tmp;
		tmp = tmp->next;
	}
	return (last);
}

t_ast	*parse_token(t_token *token)
{
	t_ast	*new_node;
	t_token	*left;
	t_token	*right;

	new_node = NULL;
	if (!token)
		return (NULL);
	if (token->type == TYPE_PIPE)
	{
		left = get_prev_executable(token);
		right = get_next_executable(token);
		new_node->pipe.left = parse_token(left);
		new_node->pipe.right = parse_token(right);
		new_node = create_pipe(new_node->pipe.left, new_node->pipe.right);
		// if (!new_node || !right || !left)
		// 	return (NULL);
		return (new_node);
	}
	while (token->prev && (token->prev->type == TYPE_ARG
			|| token->prev->type == TYPE_SPACE))
		token = token->prev;
	if (token->type == TYPE_CMD)
		return (create_command(token));
	return (NULL);
}

// t_token	*get_prioritary_token(t_token *token_node, int priority)
// {
// 	while (token_node)
// 	{
// 		if (token_node->priority == priority)
// 			return (token_node);
// 		token_node = token_node->prev;
// 		priority++;
// 	}
// 	return (token_node);
// }

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

int	init_ast(t_ast **ast_lst, t_token **token_lst)
{
	t_token	*root_token;

	if (!token_lst || !*token_lst)
		return (1);
	root_token = get_root_token(token_lst, 0);
	if (!root_token)
		return (1);
	*ast_lst = parse_token(root_token);
	print_ast(*ast_lst, 0);
	return (0);
}

// 	t_token	*token;
// 	int	priority;

// 	priority = 0;
// 	token = get_last_token(*token_lst);
// 	token = (get_prioritary_token(token, priority));
// 	*ast_lst = parse_token(*token_lst);
// 	if ((*ast_lst)->type == PIPE)
// 		ft_printf("head = |\n");
// 	if ((*ast_lst)->type == COMMAND)
// 		ft_printf("head = %s", (*ast_lst)->command.args[0]);

// 	// t_token	*next_token;
// 	// t_ast	*new_ast_node;
// 	// int		priority;

// 	// priority = 0;
// 	// while (priority <= 5)
// 	// {
// 	// 	next_token = get_last_token(*token_lst);
// 	// 	while (next_token)
// 	// 	{
// 	// 		if (next_token->priority == priority)
// 	// 		{
// 	// 			new_ast_node = add_ast_node(ast_lst);
// 	// 			set_ast_node(new_ast_node, next_token);
// 	// 		}
// 	// 		next_token = next_token->prev;
// 	// 	}
// 	// 	priority++;
// 	// }
// 	return (0);
// }

//	chercher le node