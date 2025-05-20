#include "ast.h"
#include "token.h"
static int	set_token_node(t_token *token_node, char *content)
{
	if (set_token_content(token_node, content))
		return (-1); 
	if (set_token_type(token_node))
		return (-1);
	return (0);
}

int	init_token(t_token **token_lst, char *input)
{
	t_token	*new_token;
	int		i;

	*token_lst = NULL;
	i = 0;
	while (input[i] && input[i] != '\n')
	{
		new_token = add_token_node(token_lst);
		if (!new_token)
			return (-1);
		if (set_token_node(new_token, &input[i]) == -1)
			return(-1);
		i += get_token_len(&input[i]);
	}
	return (0);
}

int	init_ast(t_ast **ast_lst, t_token *token_node)
{
	t_ast	*new_node;

	while (token_node)
	{
		new_node = add_ast_node(ast_lst);
		if (!new_node)
			return (-1);
		if (set_ast_node(new_node, token_node) == -1)
			return (-1);
		token_node = token_node->next;
	}
	return (0);
}