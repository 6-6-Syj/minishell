/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:11:05 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/23 21:36:02 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

/****************************************************************************/
/*                                INCLUDE									*/
/****************************************************************************/
# include "token.h"
/****************************************************************************/
/*                                ENUM										*/
/****************************************************************************/
typedef enum e_type_ast
{
	AND,
	OR,
	PIPE,
	REDIR_IN_TRUNC,
	REDIR_OUT_TRUNC,
	REDIR_OUT_APPEND,
	HERE_DOC,
	COMMAND,
}					t_type_ast;

typedef struct s_command
{
	char			**args;
}					t_command;

typedef struct s_pipe
{
	struct s_ast	*left;
	struct s_ast	*right;
}					t_pipe;

typedef struct s_ast
{
	t_type_ast		type;
	union
	{
		t_command	command;
		t_pipe		pipe;
		// t_redirect	redirect;
	};
}					t_ast;

// typedef struct s_redirect
// {
// 	struct s_ast	*child;
// 	char			*filename;
// 	int mode; // par ex. O_WRONLY, O_RDONLY
// }					t_redirect;


/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/
// typedef struct s_ast
// {
// 	t_type_ast		type;
// 	char			**args;
// 	struct s_ast	*left;
// 	struct s_ast	*right;
// }					t_ast;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
// void	init_ast_lst(t_ast **ast_lst); // test version
int					init_ast(t_ast **ast_lst, t_token **token_lst);
t_ast				*add_ast_node(t_ast **ast_lst);
t_ast	*parse_token(t_token *token);

#endif
