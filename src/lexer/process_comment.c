/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_comment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 22:05:30 by yliu              #+#    #+#             */
/*   Updated: 2024/09/04 10:21:20 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

t_token_list	*process_comment(t_lexer *lexer)
{
	lexer->type = TOKEN_EOF;
	lexer->value = NULL;
	return (construct_token(lexer->type, lexer->value));
}
