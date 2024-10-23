/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_parse_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 02:28:39 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/22 22:21:20 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include "token.h"
#include "utils.h"

bool	is_redirect_token(t_token_type type)
{
	return (type == TOKEN_LESS
		|| type == TOKEN_GREAT
		|| type == TOKEN_DLESS
		|| type == TOKEN_DGREAT);
}

bool	try_parse_redirect(t_ast *node, t_token_list **cur_token)
{
	t_redirect_info		redirect_info;
	t_token_type		token_type;
	t_heredoc_status	status;

	token_type = get_token_type(*cur_token);
	if (get_token_type(*cur_token) != token_type)
		return (false);
	redirect_info.type = (t_redirect_type)token_type;
	consume_token(cur_token);
	if (get_token_type(*cur_token) != TOKEN_WORD)
		return (false);
	redirect_info.file_or_delim = get_token_value(*cur_token);
	consume_token(cur_token);
	if (redirect_info.type == REDIRECT_HEREDOC)
	{
		status = handle_heredoc(redirect_info.file_or_delim, &redirect_info);
		if (status == HEREDOC_FAILURE)
			print_error("heredoc", "failed to open heredoc file");
		else if (status == HEREDOC_INTERRUPTED)
			return (abort_parse_return(node, cur_token, false));
	}
	push_redirect_info(node, &redirect_info);
	return (true);
}
