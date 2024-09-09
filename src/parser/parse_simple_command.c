/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:26:37 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/08 14:06:57 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "ast.h"
#include "parser_internal.h"
#include "token.h"
#include "utils.h"

static bool	is_redirect_token(t_token_type type)
{
	return (type == TOKEN_LESS
		|| type == TOKEN_GREAT
		|| type == TOKEN_DLESS
		|| type == TOKEN_DGREAT);
}

// TODO: Replace newline with the more appropriate token value (EOF?)
static t_ast	*handle_error(t_ast *ast, const char *token_value)
{
	if (token_value == NULL)
		token_value = "newline";
	print_syntax_error(token_value);
	destroy_ast(ast);
	return (NULL);
}

static bool	parse_word(t_ast *ast, t_token_list **cur_token)
{
	push_cmd_arg(ast, get_token_value(*cur_token));
	return (consume_token(cur_token));
}

static bool	parse_redirect(t_ast *ast, t_token_list **cur_token)
{
	t_redirect_info	redirect_info;
	t_token_type	token_type;

	token_type = get_token_type(*cur_token);
	redirect_info.type = (t_redirect_type)token_type;
	if (!expect_token(cur_token, token_type))
		return (false);
	redirect_info.filepath = get_token_value(*cur_token);
	if (!expect_token(cur_token, TOKEN_WORD))
		return (false);
	push_redirect_info(ast, &redirect_info);
	return (true);
}

/*
** simple_command   : cmd_prefix cmd_word cmd_suffix
**                  | cmd_prefix cmd_word
**                  | cmd_prefix
**                  |            cmd_word cmd_suffix
**                  |            cmd_word
**                  ;
*/
t_ast	*parse_simple_command(t_token_list **cur_token)
{
	t_ast	*ast;
	bool	is_valid;

	ast = construct_ast(AST_COMMAND, NULL, NULL);
	is_valid = true;
	while (get_token_type(*cur_token) != TOKEN_EOF)
	{
		if (get_token_type(*cur_token) == TOKEN_WORD)
			is_valid = parse_word(ast, cur_token);
		else if (is_redirect_token(get_token_type(*cur_token)))
			is_valid = parse_redirect(ast, cur_token);
		else
			break ;
		if (!is_valid)
			return (handle_error(ast, get_token_value(*cur_token)));
	}
	return (ast);
}
