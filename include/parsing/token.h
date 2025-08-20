/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/05/05 19:59:48 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/05 19:59:48 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

/****************************************************************************/
/*                                INCLUDE									*/
/****************************************************************************/
# include "error.h"
# include <stdbool.h>
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
	WORD = 0,
	AND = 1 << 0,
	OR = 1 << 1,
	PIPE = 1 << 2,
	HERE_DOC = 1 << 3,
	REDIR_IN = 1 << 4, // TRUNC
	REDIR_OUT = 1 << 5, // TRUNC
	REDIR_APPEND = 1 << 6, // APPEND
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
} t_type;

// if (type == REDIR)
// if (type & REDIR)

// if (type != REDIR)
// if (type & !REDIR)
/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/
typedef struct s_data t_data;

typedef struct s_token
{
	int				err;
	int				priority;
	int				type;
	char			*content;
	struct s_token	*prev;
	struct s_token	*next;
}					 t_token;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
t_type	get_token_type(t_token *token);
void	init_token(t_data *data);
t_token	*add_token_node(t_token **token_lst);
void	free_token_node(t_token *token_node);
void	free_token_lst(t_token **token_lst);
int		get_token_len(char *token);
bool	is_part_of_word(char c);
bool	is_quote(char c);
bool	is_expand(char *token);
bool	is_operator(char c);
t_token	*get_last_token(t_token *lst);
int		remove_node(t_token *node, t_data *data);
int		remove_space(t_token **token_lst, t_data *data);
void	add_next_token_node(t_token **current);
void	add_prev_token_node(t_token **current);
char	*handle_expand(char *token, int i, t_data *data);
void	set_command_type(t_token **token_lst);
void	set_token_type(t_token **token_lst, t_data *data);
void	set_file_type(t_token **token_lst);
void	remove_quote(char **token_content, t_data *data);
void	remove_simple_quote(t_token **token_lst, t_data *data);
void	remove_double_quote(t_token **token_lst, t_data *data);
void	expand_var(t_token **token_lst, t_data *data);
void	join_word(t_token **token_lst, t_data *data);
int		get_token_priority(t_token *token);
void	set_token_priority(t_token **token_lst);
int		get_expand_key_len(char *token_content);
char	*get_expand(char *token, t_data *data);
bool	is_space(char c);
#endif
