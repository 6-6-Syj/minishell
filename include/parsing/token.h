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
	TYPE_WORD = 0,		// 0000 0000
	TYPE_AND = 1 << 0,	// 0000 0001
	TYPE_OR = 1 << 1,	// 0000 0010
	TYPE_PIPE = 1 << 2, // 0000 0100
	TYPE_HERE_DOC = 1 << 3,
	TYPE_REDIR_IN = 1 << 4,
	TYPE_REDIR_OUT = 1 << 5,
	TYPE_REDIR_APPEND = 1 << 6,
	TYPE_QUOTE_S = 1 << 7,
	TYPE_QUOTE_D = 1 << 8,
	TYPE_PAREN_L = 1 << 9,
	TYPE_PAREN_R = 1 << 10,
	TYPE_CMD = 1 << 11,
	TYPE_ARG = 1 << 12,
	TYPE_NEW_LINE = 1 << 13,
	TYPE_SPACE = 1 << 14,
	TYPE_UNKNOWN = 1 << 15,
	TYPE_FILE = 1 << 16,
	TYPE_EXPAND = 1 << 17,
	TYPE_VAR = 1 << 18,
	TYPE_REDIR = TYPE_REDIR_IN | TYPE_REDIR_OUT | TYPE_REDIR_APPEND | TYPE_HERE_DOC,
	TYPE_OPERATOR = TYPE_AND | TYPE_OR | TYPE_PIPE
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
