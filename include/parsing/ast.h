/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:11:05 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/09/02 19:08:25 by dabuchhe         ###   ########lyon.fr   */
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
	int						fd_in;
	int						fd_out;
	char					**args;
	bool					is_last_cmd;
	struct s_redir			*redir;
}							t_command;

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
/*init_ast*/
int					init_ast(t_ast **ast_lst, t_token **token_lst,
						t_data *data);

/*free_ast*/
void				free_ast(t_ast **node);

/*ast_utils*/
int					get_args_len(t_token *token);
t_token				*get_prev_priority_token(t_token *root_token);
t_token				*get_next_priority_token(t_token *root_token);
t_token				*get_root_token(t_token **token_lst, int priority);

#endif
