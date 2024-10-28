/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_parse_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 02:28:39 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/27 09:43:59 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include "token.h"
#include "utils.h"

bool	is_redirect_first_set(t_token_list *cur_token)
{
	t_token_type	type;

	type = get_token_type(cur_token);
	return (type == TOKEN_LESS
		|| type == TOKEN_GREAT
		|| type == TOKEN_DLESS
		|| type == TOKEN_DGREAT);
}

t_parse_status	try_parse_redirect(t_ast *node, t_token_list **cur_token)
{
	t_redirect_info	*redirect_info;
	t_redirect_type	type;
	const char		*file_or_delim;
	t_parse_status	status;

	type = (t_redirect_type)get_token_type(*cur_token);
	consume_token(cur_token);
	if (get_token_type(*cur_token) != TOKEN_WORD)
		return (PARSE_FAILURE);
	file_or_delim = get_token_value(*cur_token);
	consume_token(cur_token);
	redirect_info = construct_redirect_info(type, file_or_delim);
	if (type == REDIRECT_HEREDOC)
	{
		status = handle_heredoc(file_or_delim, redirect_info);
		if (redirect_info->heredoc_fd == -1)
			print_error("heredoc", "failed to open heredoc file");
		else if (status == PARSE_ABORT)
			return (PARSE_ABORT);
	}
	push_redirect_info(node, redirect_info);
	return (PARSE_SUCCESS);
}
