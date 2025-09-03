/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-31 17:22:02 by jmagand           #+#    #+#             */
/*   Updated: 2025-08-31 17:22:02 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

/****************************************************************************/
/*                                INCLUDE									*/
/****************************************************************************/
# include <stdbool.h>
# include <stdlib.h>
# include <sys/types.h>

/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/
typedef struct s_token		t_token;
typedef struct s_env		t_env;
typedef struct s_ast		t_ast;
typedef struct s_pipe		t_pipe;
typedef struct s_command	t_command;

typedef struct s_fd_backup
{
	int						fd_in;
	int						fd_out;
	int						fd_err;
}							t_fd_backup;

typedef struct s_data
{
	t_ast					*ast;
	t_env					*env;
	t_token					*token;
	t_pipe					*pipe;
	t_fd_backup				*backup;
	pid_t					last_cmd_pid;
	char					**env_tab;
	char					*err_msg;
	int						err;
	int						exit_err;
	char					*input;
	bool					exit_pipe;
	bool					sig;
	bool					syntax_err;
	int						i;
}							t_data;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
/* init_data */
void						init_data(t_data *data, char **env);

/* free_data */
void						free_data(t_data *data);
void						free_tmp_data(t_data *data);

/* error */
void						exit_error(t_data *data);
void						cmd_not_found(t_command *cmd, t_data *data);
void						no_file_or_directory(t_command *cmd, t_data *data);
void						malloc_fail(t_data *data);
void						syntax_error(t_data *data);
#endif
