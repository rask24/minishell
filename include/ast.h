/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:41:56 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/05 19:14:09 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "libft.h"
# include "token.h"

typedef enum e_ast_node_type
{
	AST_COMMAND,
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_SUBSHELL,
	AST_REDIRECT
}					t_ast_node_type;

typedef enum e_redirect_type
{
	REDIRECT_INPUT = TOKEN_GREAT,
	REDIRECT_OUTPUT = TOKEN_LESS,
	REDIRECT_APPEND = TOKEN_DGREAT,
	REDIRECT_HEREDOC = TOKEN_DLESS,
}					t_redirect_type;

typedef struct s_redirect_info
{
	t_redirect_type	type;
	const char		*filename;
}					t_redirect_info;

typedef struct s_ast
{
	t_ast_node_type	type;
	struct s_ast	*left;
	struct s_ast	*right;
	t_list			*cmd_args;
	t_list			*redirects;
}					t_ast;

t_ast				*construct_ast(t_ast_node_type type,
						t_ast *left, t_ast *right);
t_redirect_info		*construct_redirect_info(t_redirect_type type,
						const char *filename);
void				destroy_ast(t_ast *ast);
void				push_cmd_arg(t_ast *ast, const char *cmd_arg);
void				push_redirect_info(t_ast *ast, t_redirect_info *info);
const char			*get_cmd_arg(t_list *cmd_args);
t_redirect_type		get_redirect_type(t_list *redirects);
const char			*get_redirect_filename(t_list *redirects);

#endif