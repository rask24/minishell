/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_comment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 22:05:30 by yliu              #+#    #+#             */
/*   Updated: 2024/08/31 22:07:40 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

void	process_comment(t_lexer *lexer)
{
	lexer->value = NULL;
	lexer->type = TOKEN_EOF;
}
