/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:15:04 by yliu              #+#    #+#             */
/*   Updated: 2024/08/30 13:30:51 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct s_lexer_state {
  char *start;
  char *end;
  bool is_inside_quote;
} t_lexer_state;

t_token_list *lexer(const char *string);

#endif
