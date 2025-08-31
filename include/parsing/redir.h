/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:44:25 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/06/30 18:43:15 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

/****************************************************************************/
/*                                INCLUDE									*/
/****************************************************************************/
# include "ast.h"
# include "data.h"
# include "libft.h"
# include <signal.h>
# include <stdio.h>
# include <unistd.h>

/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/
typedef struct s_redir
{
	t_type					type;
	char					*filename;
	char					*delimiter;
	struct s_redir			*prev;
	struct s_redir			*next;
}							t_redir;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
t_redir						*add_redir_node(t_redir **redir_lst);
void						init_redir(t_token *token_node, t_redir **redir_lst,
								t_data *data);
void						open_files(t_command *cmd, t_data *data);
bool						is_last_command_in_ast(t_ast *root);

/* here_doc */
void						set_here_doc(t_redir **redir_node, t_data *data);

/* here_doc_utils */
bool						ctrl_c_catched(char *line, int fd, char *filename);
bool						eof_catched(char *line, int fd, t_redir *redir,
								t_data *data);

#endif
