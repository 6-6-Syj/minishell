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
# include "libft.h"
# include "print.h"
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
	TYPE_PARENTHESE,
	TYPE_OPERATOR,
	TYPE_PIPE,
	TYPE_REDIRECTION,
	TYPE_COMMAND,
	TYPE_EXPAND,
	TYPE_QUOTE,
	TYPE_SPACE,
}	t_type;

/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/
typedef struct s_token
{
	int				err;
	int				value;
	char			*content;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
void	free_token(t_token *token);
t_token	*get_last_token(t_token *lst);
int		get_token_len(char *token);
bool	is_a_delimiter(char c);
void	set_token_value(t_token *head);
void	set_token_content(t_token *token, char *new_content);
t_token	*add_token_node(t_token *token_lst);
void	init_token(t_token *token_lst, char *input);

#endif
