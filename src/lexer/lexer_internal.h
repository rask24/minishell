/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:25:14 by yliu              #+#    #+#             */
/*   Updated: 2024/10/27 17:36:08 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_INTERNAL_H
# define LEXER_INTERNAL_H

# include "token.h"

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

typedef struct s_lexer
{
	const char		*left;
	const char		*right;
	char			*value;
	t_token_type	type;
}					t_lexer;

t_token_list		*get_next_token(t_lexer *lexer);
bool				is_start_of_input(t_lexer *lexer);

t_token_list		*process_blank(t_lexer *lexer);
t_token_list		*process_comment(t_lexer *lexer);
t_token_list		*process_eof(t_lexer *lexer);
t_token_list		*process_operator(t_lexer *lexer);
t_token_list		*process_quote(t_lexer *lexer);
t_token_list		*process_word(t_lexer *lexer);

#endif
