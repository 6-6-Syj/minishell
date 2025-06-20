/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:59:37 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/05 21:59:37 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

/* ************************************************************************** */
/*                                INCLUDE	                                  */
/* ************************************************************************** */
# include "minishell.h"

/* ************************************************************************** */
/*                                STRUCT	                                  */
/* ************************************************************************** */
typedef struct s_data	t_data;
typedef struct s_token	t_token;
typedef struct s_redir	t_redir;

/* ************************************************************************** */
/*                                FUNCTIONS                                   */
/* ************************************************************************** */
void	print_data(t_data *data);
void	print_token_lst(t_token *token_lst);
void	print_ast_lst(t_ast *ast_lst);
void	print_all(t_data *data);
void	print_redir_lst(t_redir *redir);
void 	print_ast_graphical(t_ast *root);
#endif