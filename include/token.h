/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:27:54 by yliu              #+#    #+#             */
/*   Updated: 2024/08/19 14:18:03 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_AND_IF,
	TOKEN_OR_IF,
	TOKEN_L_PARENTHESIS,
	TOKEN_R_PARENTHESIS,
	TOKEN_PIPE,
	TOKEN_LESS,
	TOKEN_DLESS,
	TOKEN_GREAT,
	TOKEN_DGREAT,
	TOKEN_EOF,
	TOKEN_UNKNOWN
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}					t_token;

t_token				*construct_token(char *string, t_token_type type);
void				destroy_token(t_token *token);
char				*get_token_value(t_token *token);
t_token_type		get_token_type(t_token *token);

typedef t_list		t_token_list;

t_token_list		*construct_token_list(void);
void				push_back_token(t_token_list **list, t_token *token);
void				destroy_token_list(t_token_list *list);

#endif
