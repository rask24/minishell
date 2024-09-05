/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:27:54 by yliu              #+#    #+#             */
/*   Updated: 2024/08/30 15:32:32 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdlib.h>

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
	t_token_type	type;
	char			*value;
}					t_token;

typedef t_list		t_token_list;

t_token_list		*construct_token(t_token_type type, char *string);
void				destroy_token(t_token_list *token);
t_token_type		get_token_type(t_token_list *token);
char				*get_token_value(t_token_list *token);
void				destroy_token_list(t_token_list *list);

#endif
