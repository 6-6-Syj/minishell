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
	TYPE_WORD,
	TYPE_REDIR_IN,
	TYPE_REDIR_OUT,
	TYPE_REDIR_APPEND,
	TYPE_HERE_DOC,

	TYPE_PIPE,
	TYPE_AND,
	TYPE_OR,

	TYPE_PAREN_L,
	TYPE_PAREN_R,
	TYPE_NEW_LINE,
	TYPE_QUOTE_S,
	TYPE_QUOTE_D,
	TYPE_SPACE,
	TYPE_UNKNOWN,
}	t_type;

/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/
typedef	struct s_data	t_data;

typedef struct s_token
{
	int				err;
	int				type;
	char			*content;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
void	init_token(t_token **token_lst, char *input);
t_token	*add_token_node(t_token **token_lst);
t_token	*get_last_token(t_token *token_lst);
void	set_token_value(t_token *token_lst);
void	set_token_content(t_token **token, char *new_content);
void	free_token(t_token *token_lst);
bool	is_delimiter(char c);
int		get_token_len(char *token);

#endif
