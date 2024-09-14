/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:22:57 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/14 21:10:14 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include <stdbool.h>

# include "ast.h"
# include "token.h"

t_ast	*parse_simple_command(t_token_list **cur_token);
t_ast	*parse_pipeline(t_token_list **cur_token);
t_ast	*parse_list(t_token_list **cur_token);

bool	consume_token(t_token_list **cur_token);
bool	expect_token(t_token_list **cur_token, t_token_type type);
t_ast	*handle_error(t_ast *ast, const char *token_value);

#endif
