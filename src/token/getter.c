/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:12:08 by yliu              #+#    #+#             */
/*   Updated: 2024/08/19 13:28:34 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

char	*get_token_value(t_token *token)
{
	return (token->value);
}

t_token_type	get_token_type(t_token *token)
{
	return (token->type);
}
