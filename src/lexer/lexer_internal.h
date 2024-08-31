/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:25:14 by yliu              #+#    #+#             */
/*   Updated: 2024/08/31 14:25:03 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_INTERNAL_H
# define LEXER_INTERNAL_H

# include "token.h"

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

typedef struct s_lexer
{
	char			*left;
	char			*right;
	char			*value;
	t_token_type	type;
}					t_lexer;

void				construct_lexer(char *input, t_lexer *lexer);
void				delimit_token(t_lexer *lexer);
t_token_list		*get_next_token(t_lexer *lexer);
void				process_blank(t_lexer *lexer);
void				process_eof(t_lexer *lexer);
void				process_quote(t_lexer *lexer, char left_quote_char);

#endif
