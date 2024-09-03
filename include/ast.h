/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:41:56 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/03 21:55:32 by reasuke          ###   ########.fr       */
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
}	t_ast_node_type;

typedef enum e_redirect_type
{
	REDIRECT_INPUT = TOKEN_GREAT,
	REDIRECT_OUTPUT = TOKEN_LESS,
	REDIRECT_APPEND = TOKEN_DGREAT,
	REDIRECT_HEREDOC = TOKEN_DLESS,
}	t_redirect_type;

typedef struct s_redirect_info
{
	t_redirect_type	type;
	const char		*filename;
}	t_redirect_info;

typedef struct s_ast
{
	t_ast_node_type	type;
	struct s_ast	*left;
	struct s_ast	*right;
	t_list			*cmd_args;
	t_list			*redirects;
}	t_ast;

#endif
