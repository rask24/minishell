/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:54:34 by yliu              #+#    #+#             */
/*   Updated: 2024/09/13 17:29:41 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ast.h"
#include "exec_internal.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"

void	exec(char *input, char **envp)
{
	t_token_list	*token_list;
	t_ast			*ast;

	token_list = lexer(input);
	if (token_list == NULL)
		return ;
	ast = parser(token_list);
	if (ast == NULL)
	{
		destroy_token_list(token_list);
		return ;
	}
	if (ast->type == AST_PIPE || ast->type == AST_COMMAND)
		execute_pipeline(ast, envp, STDIN_FILENO, STDOUT_FILENO);
	else
		print_error("exec", "unsupported AST type");
	destroy_token_list(token_list);
	destroy_ast(ast);
}
