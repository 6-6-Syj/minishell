/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:59:48 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/05 19:59:48 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

/****************************************************************************/
/*                                INCLUDE									*/
/****************************************************************************/
#include <stdbool.h>
#include "error.h"
/****************************************************************************/
/*                                DEFINE									*/
/****************************************************************************/
# define C_SPACE ' '
# define C_SIMPLE_QUOTE '\''
# define C_DOUBLE_QUOTE '\"'


/****************************************************************************/
/*                                ENUM										*/
/****************************************************************************/
typedef enum e_type
{
	WORD,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HERE_DOC,

	PIPE,
	AND,
	OR,

	CMD,
	ARG,
	PAREN_L,
	PAREN_R,
	NEW_LINE,
	QUOTE_S,
	QUOTE_D,
	SPACE,
	UNKNOWN,
	REDIR_TARGET,
	REDIR,
	EXPAND,
	VAR
}	t_type;

/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/
typedef	struct s_data	t_data;

typedef struct s_token
{
	int				err;
	int				priority;
	int				type;
	char			*content;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
int		get_token_priority(t_token *token);
t_type	get_token_type(t_token *token);
t_type	get_token_word_type(t_token *token);
int	init_token(t_token **token_lst, char *input);
t_token	*add_token_node(t_token **token_lst);
void	free_token_node(t_token *token_node);
void	free_token_lst(t_token **token_lst);
int		get_token_len(char *token);
bool	is_delimiter(char c);
bool	is_part_of_word(char c);
bool	is_parenthesis(char c);
bool	is_quote(char c);
bool	is_operator(char c);
t_token	*get_last_token(t_token *lst);

#endif
