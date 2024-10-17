/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:22:57 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/17 20:34:16 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include <stdbool.h>

# include "ast.h"
# include "token.h"

typedef bool	(*t_parse_simple_commnad)(t_ast *node, t_token_list **token);

t_ast	*parse_simple_command(t_token_list **cur_token);
t_ast	*parse_pipeline(t_token_list **cur_token);
t_ast	*parse_command(t_token_list **cur_token);
t_ast	*parse_list(t_token_list **cur_token);

bool	try_parse_redirect(t_ast *node, t_token_list **cur_token);
bool	is_redirect_token(t_token_type type);

void	handle_heredoc(const char *delimiter, t_redirect_info *info);
int		create_heredoc(t_list *input_list, size_t heredoc_size);

bool	consume_token(t_token_list **cur_token);
bool	expect_token(t_token_list **cur_token, t_token_type type);
t_ast	*handle_syntax_error(t_ast *node, const char *token_value);

#endif
