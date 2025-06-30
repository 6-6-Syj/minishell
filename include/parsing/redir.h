/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:44:25 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/06/28 18:39:49 by dabuchhe         ###   ########lyon.fr   */
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

/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/
typedef struct s_redir
{
	t_type			type;
	char			*filename;
	char			*delimiter;
	struct s_redir	*prev;
	struct s_redir	*next;
}					t_redir;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
t_redir				*add_redir_node(t_redir **redir_lst);
void				init_redir(t_token *token_node, t_redir **redir_lst, t_data *data);
void				open_files(t_command *cmd, t_data *data);
void				free_pid_list(t_pid_list *pids);
bool				is_last_command_in_ast(t_command *cmd, t_ast *root);
void				set_here_doc(t_redir **redir_node, t_data *data);
// void				set_here_doc(t_redir **redir_node, t_data *data);

#endif
