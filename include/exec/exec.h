/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-09 18:36:03 by jmagand           #+#    #+#             */
/*   Updated: 2025-05-09 18:36:03 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/****************************************************************************/
/*                                INCLUDE									*/
/****************************************************************************/
# include "ast.h"
# include "data.h"
# include "libft.h"
# include "wrappers.h"
# include <stdio.h>
# include <sys/wait.h>

/****************************************************************************/
/*                                DEFINE									*/
/****************************************************************************/

/****************************************************************************/
/*                                ENUM										*/
/****************************************************************************/

/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/
typedef struct s_data	t_data;
typedef struct s_ast	t_ast;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
/* handle_end_process */
void					log_process_end(pid_t wpid, int status);
int						get_exit_code(int status);
void					handle_end_process(pid_t wpid, int status);
void					clean_all_processes(t_pid_list *pids);

void					handle_ast(t_ast *node, t_data *data, int *fd,
							t_pid_list **pids);

void					exec_ast(t_ast *node, t_data *data);
void					exec_and_restore_fd(t_fd_backup *backup, t_command *cmd,
							t_data *data);

char					*get_path(char *cmd, t_data *data);
char					**split_path(t_data *data);
int						is_absolute_or_relative_path(char *cmd);
void					*free_strs(char **strs);

#endif
