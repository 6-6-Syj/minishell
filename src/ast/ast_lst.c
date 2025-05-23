#include "ast.h"
#include "unistd.h"
#include "libft.h"


// t_ast	*add_ast_node(t_ast **ast_lst)
// {
// 	t_ast	*new_node;

// 	new_node = ft_calloc(1, sizeof(t_ast));
// 	if (!new_node)
// 		return (NULL) ; // NEED PROTEC
// 	if (!*ast_lst)
// 		*ast_lst = new_node;
// 	else if (!(*ast_lst)->left)
// 		(*ast_lst)->left = new_node;
// 	else if (!(*ast_lst)->right)
// 		(*ast_lst)->right = new_node;
// 	new_node->left = NULL; // NEEDED ?
// 	new_node->right = NULL; // NEEDED ?
// 	return (new_node);
// }