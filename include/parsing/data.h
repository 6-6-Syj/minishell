/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-24 20:10:26 by jmagand           #+#    #+#             */
/*   Updated: 2025-06-24 20:10:26 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

/****************************************************************************/
/*                                INCLUDE									*/
/****************************************************************************/
# include <stdlib.h>
# include <stdbool.h>

/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/
typedef struct s_token		t_token;
typedef struct s_env		t_env;
typedef struct s_ast		t_ast;
typedef struct s_pipe		t_pipe;

typedef struct s_pid_list
{
	pid_t				pid;
	bool				is_last_cmd;
	struct s_pid_list	*next;
}						t_pid_list;

typedef struct s_fd_backup
{
	int					fd_in;
	int					fd_out;
	int					fd_err;
}						t_fd_backup;

typedef struct s_data
{
	t_ast				*ast;
	t_env				*env;
	t_token				*token;
	t_pipe				*pipe;
	t_fd_backup			*backup;
	t_pid_list			*pid_list;
	char				**env_tab;
	char				*err_msg;
	int					err;
	int					exit_err;
	char				*input;
}	t_data;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
void	init_data(t_data *data, char **env);
void	free_data(t_data *data);
void	exit_error(t_data *data);

#endif
