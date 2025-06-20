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
	WORD = 0,		// 0000 0000
	AND = 1 << 0,	// 0000 0001
	OR = 1 << 1,	// 0000 0010
	PIPE = 1 << 2, // 0000 0100
	HERE_DOC = 1 << 3,
	REDIR_IN = 1 << 4,
	REDIR_OUT = 1 << 5,
	REDIR_APPEND = 1 << 6,
	QUOTE_S = 1 << 7,
	QUOTE_D = 1 << 8,
	PAREN_L = 1 << 9,
	PAREN_R = 1 << 10,
	CMD = 1 << 11,
	ARG = 1 << 12,
	NEW_LINE = 1 << 13,
	SPACE = 1 << 14,
	UNKNOWN = 1 << 15,
	REDIR_TARGET = 1 << 16,
	EXPAND = 1 << 17,
	VAR = 1 << 18,
	REDIR = REDIR_IN | REDIR_OUT | REDIR_APPEND | HERE_DOC,
	OPERATOR = AND | OR | PIPE
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
int		init_token(t_token **token_lst, char *input);
t_token	*add_token_node(t_token **token_lst);
void	free_token_node(t_token *token_node);
void	free_token_lst(t_token **token_lst);
int		get_token_len(char *token);
bool	is_delimiter(char c);
bool	is_part_of_word(char c);
bool	is_parenthesis(char c);
bool	is_quote(char c);
bool	is_operator(char c);
int		parse_token_lst(t_token **token_lst);
t_token	*get_last_token(t_token *lst);

#endif
