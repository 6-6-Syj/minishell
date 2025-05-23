/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:11:05 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/05 20:11:05 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

/****************************************************************************/
/*                                INCLUDE									*/
/****************************************************************************/
# include <stdlib.h>

/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/
typedef struct s_token	t_token;
typedef struct s_env	t_env;
typedef struct s_ast	t_ast;
typedef struct s_pipe	t_pipe;

typedef struct s_data
{
	t_ast	*ast;
	t_env	*env;
	t_token	*token;
	t_pipe	*pipe;
	char	**env_tab;
	char	*err_msg;
	int		err;
}	t_data;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
void	init_data(t_data *data);
void	free_data(t_data *data);
void	exit_error(t_data *data);

#endif
