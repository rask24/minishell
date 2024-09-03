/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:28:06 by yliu              #+#    #+#             */
/*   Updated: 2024/09/03 18:01:04 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token_list	*construct_token(t_token_type type, char *string)
{
	t_token			*content;
	t_token_list	*token;

	content = (t_token *)ft_xmalloc(sizeof(t_token));
	content->type = type;
	content->value = string;
	token = ft_xlstnew(content);
	return (token);
}
