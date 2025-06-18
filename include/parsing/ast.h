/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:11:05 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/29 16:53:57 by dabuchhe         ###   ########lyon.fr   */
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
// typedef struct s_redirect
// {
// 	struct s_ast	*child;
// 	char			*filename;
// 	int mode; // par ex. O_WRONLY, O_RDONLY
// }					t_redirect;

/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/

typedef struct s_logic
{
	struct s_ast	*left;
	struct s_ast	*right;
}					t_logic;

typedef struct s_command
{
	int				fd_in;
	int				fd_out;
	char			**args;
	struct s_redir	*redir;
}					t_command;

typedef struct s_pipe
{
	struct s_ast	*left;
	struct s_ast	*right;
}					t_pipe;

typedef struct s_redir
{
	char			*target;
	struct s_redir	*next;
}					t_redir;

typedef struct s_ast
{
	t_type			type;
	union
	{
		t_logic		logic;
		t_command	command;
		t_pipe		pipe;
		t_redir		redir;
	};
}					t_ast;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
// void	init_ast_lst(t_ast **ast_lst); // test version
int					init_ast(t_ast **ast_lst, t_token **token_lst);
t_ast				*add_ast_node(t_ast **ast_lst);
t_ast				*parse_token(t_token *token);
void				free_ast(t_ast **node);

#endif
