/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:03:25 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/09/02 17:03:25 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

/****************************************************************************/
/*                                INCLUDE									*/
/****************************************************************************/
# include <stdbool.h>

/****************************************************************************/
/*                                ENUM										*/
/****************************************************************************/
typedef enum e_type
{
	WORD = 0,
	PIPE = 1 << 0,
	HERE_DOC = 1 << 1,
	REDIR_IN = 1 << 2,
	REDIR_OUT = 1 << 3,
	REDIR_APPEND = 1 << 4,
	QUOTE_S = 1 << 5,
	QUOTE_D = 1 << 6,
	CMD = 1 << 7,
	ARG = 1 << 8,
	SPACE = 1 << 9,
	UNKNOWN = 1 << 10,
	REDIR_TARGET = 1 << 11,
	EXPAND = 1 << 12,
	REDIR = REDIR_IN | REDIR_OUT | REDIR_APPEND | HERE_DOC,
}						t_type;

/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/
typedef struct s_data	t_data;

typedef struct s_token
{
	int					err;
	int					priority;
	int					type;
	char				*content;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
/*expand_utils*/
int						get_expand_key_len(char *token_content);
char					*get_expand(char *token, t_data *data);
bool					is_expand(char *token);

/*expand*/
char					*handle_expand(char *token, int i, t_data *data);
void					expand_var(t_token **token_lst, t_data *data);

/*free_token*/
void					free_token_lst(t_token **token_lst);

/*get_type*/
t_type					get_token_type(t_token *token);

/*init_token*/
void					init_token(t_data *data);

/*quote*/
void					remove_simple_quote(t_token **token_lst, t_data *data);
void					remove_double_quote(t_token **token_lst, t_data *data);

/*set_type*/
void					set_command_type(t_token **token_lst);
void					set_token_type(t_token **token_lst);
void					set_file_type(t_token **token_lst);

/*syntax*/
bool					syntax_is_valid(t_token *token);

/*token_bool*/
bool					is_part_of_word(char c);
bool					is_quote(char c);
bool					is_operator(char c);
bool					is_space(char c);

/*token_lst*/
t_token					*add_token_node(t_token **token_lst);

/*token_utils*/
int						get_token_len(char *token);
int						remove_node(t_token *node, t_data *data);
void					join_word(t_token **token_lst, t_data *data);
void					set_token_priority(t_token **token_lst);

#endif
