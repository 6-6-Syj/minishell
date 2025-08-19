/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-27 19:02:10 by jmagand           #+#    #+#             */
/*   Updated: 2025-05-27 19:02:10 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

/****************************************************************************/
/*                                INCLUDE									*/
/****************************************************************************/
# include "ast.h"
# include "builtins.h"
# include "data.h"
# include "exec.h"

/****************************************************************************/
/*                                DEFINE									*/
/****************************************************************************/

/****************************************************************************/
/*                                ENUM										*/
/****************************************************************************/
typedef enum e_path_status
{
	PATH_OK,
	PATH_NOT_FOUND,
	PATH_UNSET
}							t_path_status;

/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/
typedef struct s_data		t_data;
typedef struct s_ast		t_ast;
typedef struct s_command	t_command;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/

/* handle_end_process */
void						handle_command(t_command *cmd, t_data *data,
								t_pid_list **pids, t_ast *root);

/* command_utils */
void						close_inherited_fds(t_command *cmd);
void						redir(t_command *cmd, t_data *data);
void						redir_builtin_solo(int *fd_in, int *fd_out,
								t_data *data);
bool						is_a_dir(t_command *cmd, t_data *data);

/* handle_fds_builtin */
int							backup_fds(t_fd_backup *backup);
void						restore_fds(t_fd_backup *backup, t_data *data);
void						unset_redirect_fds(t_command *cmd);

#endif
