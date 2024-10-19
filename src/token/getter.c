/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:12:08 by yliu              #+#    #+#             */
/*   Updated: 2024/10/18 21:18:49 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

char	*get_token_value(t_token_list *token)
{
	if (token == NULL)
		return (NULL);
	return (((t_token *)token->content)->value);
}

t_token_type	get_token_type(t_token_list *token)
{
	if (token == NULL)
		return (TOKEN_UNKNOWN);
	return (((t_token *)token->content)->type);
}
