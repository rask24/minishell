/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:28:06 by yliu              #+#    #+#             */
/*   Updated: 2024/08/19 13:29:02 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token	*construct_token(char *value, t_token_type type)
{
	t_token	*token;

	token = (t_token *)ft_xmalloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	return (token);
}

t_token_list	*construct_token_list(void)
{
	return (NULL);
}
