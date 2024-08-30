/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:25:14 by yliu              #+#    #+#             */
/*   Updated: 2024/08/30 22:53:22 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_INTERNAL_H
# define LEXER_INTERNAL_H

# include "token.h"

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

typedef struct s_lexer
{
	char		*start;
	char		*end;
}				t_lexer;

void			construct_lexer(char *string, t_lexer *lexer);
t_token_list	*get_next_token(t_lexer *lexer);
t_token_list	*process_blank(t_lexer *lexer);
void			process_quote(t_lexer *lexer, char starting_quote_char);

#endif
