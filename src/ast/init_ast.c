#include "ast.h"
#include "libft.h"
#include "token.h"
#include "unistd.h"

// t_token	*get_next_token(t_token *token_node, int priority)
// {
// 	while (token_node)
// 	{
// 		if (token_node->priority == priority)
// 			return (token_node);
// 		token_node = token_node->prev;
// 	}
// 	return (token_node);
// }

// static int	get_ast_len(t_token *token_node)
// {
// 	t_token	*token_args;
// 	int		len;

// 	token_args = token_node->next;
// 	len = 1;
// 	while (token_args && (token_args->type == TYPE_ARG || token_args->type == TYPE_SPACE))
// 	{
// 		if (token_args->type == TYPE_ARG)
// 			len++;
// 		token_args = token_args->next;
// 	}
// 	return (len);
// }

// static int	set_ast_args(t_ast *ast_node, t_token *token_node)
// {
// 	int	len;
// 	int	i;

// 	len = get_ast_len(token_node);
// 	ft_printf("len = %d\n", len);
// 	ast_node->args = ft_calloc(len, sizeof(char *) + 1);
// 	i = 0;
// 	ast_node->args[i++] = ft_strdup(token_node->content);
// 	token_node = token_node->next;
// 	while (token_node && (token_node->type == TYPE_SPACE || token_node->type == TYPE_ARG))
// 	{
// 		if (token_node->type == TYPE_ARG)
// 			ast_node->args[i++] = ft_strdup(token_node->content);
// 		token_node = token_node->next;
// 	}
// 	return (0);
// }

// static int	set_ast_node(t_ast *ast_node, t_token *token_node)
// {
// 	set_ast_args(ast_node, token_node);
// 	return (0);
// }

// int	init_ast(t_ast **ast_lst, t_token **token_lst)
// {
// 	*ast_lst = parse_token(*token_lst);
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

// static int	set_ast_node(t_ast *ast_node, t_token *token_node, int priority)
// {
// 	int	len;
// 	int	i;

// 	token_node = get_next_token(token_node, priority);
// 	len = get_ast_len();
// 	ast_node->args = ft_calloc(1, sizeof(char *) + 1);
// 	if (!ast_node->args)
// 		return (-1);
// 	i = 0;
// 	ast_node->args[i++] = ft_strdup(token_node->content);
// 	token_node = token_node->next;
// 	while (token_node)
// 	{
// 		if (token_node->type == TYPE_ARG)
// 			ast_node->args[i++] = ft_strdup(token_node->content);
// 		else if (token_node->type != TYPE_SPACE)
// 			return (0);
// 		token_node = token_node->next;
// 	}
// }