/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:15:04 by yliu              #+#    #+#             */
/*   Updated: 2024/08/29 16:39:28 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "token.h"

typedef struct s_token_buffer
{
	char			*str;
	size_t			len;
	size_t			cap;
}					t_token_buffer;

void			ft_xrealloc(t_token_buffer *token_buffer);

#endif
