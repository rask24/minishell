/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 02:28:39 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/17 02:31:10 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include "token.h"

bool	is_redirect_token(t_token_type type)
{
	return (type == TOKEN_LESS
		|| type == TOKEN_GREAT
		|| type == TOKEN_DLESS
		|| type == TOKEN_DGREAT);
}

bool	parse_redirect(t_ast *node, t_token_list **cur_token)
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
	push_redirect_info(node, &redirect_info);
	return (true);
}
