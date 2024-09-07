/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:55:24 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/07 15:15:59 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "ast.h"
#include "token.h"
#include "utils.h"

bool	consume_token(t_token_list **cur_token)
{
	if (*cur_token == NULL)
		return (false);
	*cur_token = (*cur_token)->next;
	return (true);
}

bool	expect_token(t_token_list **cur_token, t_token_type type)
{
	if (*cur_token == NULL || get_token_type(*cur_token) != type)
		return (false);
	*cur_token = (*cur_token)->next;
	return (true);
}