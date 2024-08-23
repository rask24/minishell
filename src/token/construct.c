/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:28:06 by yliu              #+#    #+#             */
/*   Updated: 2024/08/23 19:20:26 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token_list	*construct_token(t_token_type type, char *string);
{
	t_token			*content;
	t_token_list	*token;

	content = (t_token *)ft_xmalloc(sizeof(t_token));
	content->type = type;
	content->value = value;
	token = ft_lstnew(content);
	if (!token)
	{
		free(content);
		return (NULL);
	}
	return (token);
}
