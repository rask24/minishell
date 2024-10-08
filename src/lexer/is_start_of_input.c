/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_start_of_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 22:41:33 by yliu              #+#    #+#             */
/*   Updated: 2024/08/31 22:42:11 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

bool	is_start_of_input(t_lexer *lexer)
{
	return (lexer->right == lexer->left);
}
