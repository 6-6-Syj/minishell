#include "ast.h"
#include "libft.h"
#include <unistd.h>

t_ast	*add_ast_node(t_ast **ast_lst)
{
	t_ast	*new_node;

	new_node = ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		return (NULL) ; // NEED PROTEC
	if (!*ast_lst)
		*ast_lst = new_node;
	else if (!(*ast_lst)->left)
		(*ast_lst)->left = new_node;
	else if (!(*ast_lst)->right)
		(*ast_lst)->right = new_node;
	new_node->left = NULL; // NEEDED ?
	new_node->right = NULL; // NEEDED ?
	return (new_node);
}

// for "ls | cat -e" :
void	init_ast_lst(t_ast **ast_lst)
{
	t_ast	*ast_node;

	ast_node = add_ast_node(ast_lst);
	ast_node->args = ft_split("|", ' ');
	ast_node->type = PIPE;
	ast_node = add_ast_node(ast_lst);
	ast_node->args = ft_split("ls", ' ');
	ast_node->type = COMMAND;
	ast_node = add_ast_node(ast_lst);
	ast_node->args = ft_split("cat -e", ' ');
	ast_node->type = COMMAND;
}

