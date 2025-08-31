/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:11:05 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/08/25 16:01:49 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

/****************************************************************************/
/*                                INCLUDE									*/
/****************************************************************************/
# include "token.h"

/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/

typedef struct s_command
{
	int				fd_in;
	int				fd_out;
	char			**args;
	bool			is_last_cmd;
	struct s_redir	*redir;
}					t_command;

typedef struct s_pipe
{
	struct s_ast	*left;
	struct s_ast	*right;
}					t_pipe;

typedef struct s_ast
{
	t_type			type;
	union
	{
		t_command	command;
		t_pipe		pipe;
	};
}					t_ast;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
int					init_ast(t_ast **ast_lst, t_token **token_lst,
						t_data *data);
t_ast				*add_ast_node(t_ast **ast_lst);
t_ast				*create_ast_node(t_token *token, t_data *data);
void				free_ast(t_ast **node);
bool				is_command(t_token *token_node);
int					get_args_len(t_token *token);
t_token				*get_prev_priority_token(t_token *root_token);
t_token				*get_next_priority_token(t_token *root_token);
t_token				*get_root_token(t_token **token_lst, int priority);

#endif
