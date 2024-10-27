/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:41:56 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/27 09:46:41 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "libft.h"
# include "token.h"

typedef enum e_ast_node_type
{
	AST_AND = TOKEN_AND_IF,
	AST_OR = TOKEN_OR_IF,
	AST_COMMAND,
	AST_PIPE,
	AST_SUBSHELL,
	AST_ABORT,
}					t_ast_node_type;

typedef enum e_redirect_type
{
	REDIRECT_UNKNOWN = -1,
	REDIRECT_INPUT = TOKEN_LESS,
	REDIRECT_OUTPUT = TOKEN_GREAT,
	REDIRECT_APPEND = TOKEN_DGREAT,
	REDIRECT_HEREDOC = TOKEN_DLESS,
}					t_redirect_type;

typedef struct s_redirect_info
{
	t_redirect_type	type;
	const char		*file_or_delim;
	int				heredoc_fd;
	size_t			heredoc_size;
	bool			should_expand;
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

t_ast				*destroy_ast(t_ast *ast);

void				push_cmd_arg(t_ast *ast, char *cmd_arg);
void				push_redirect_info(t_ast *ast, t_redirect_info *info);

const char			*get_cmd_arg(t_list *cmd_args);
t_redirect_type		get_redirect_type(t_list *redirects);
int					get_heredoc_fd(t_list *redirects);
const char			*get_redirect_file_or_delim(t_list *redirects);
void				set_file_or_delim(t_list *redirects,
						const char *file_or_delim);

char				**convert_cmd_args_to_array(t_list *cmd_args);

#endif
