/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:40:41 by yliu              #+#    #+#             */
/*   Updated: 2024/08/23 19:35:13 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "token.h"

static void	destory_token_helper(void *content)
{
	free(((t_token *)content)->value);
	free(content);
}

void	destroy_token(t_token_list *token)
{
	ft_lstdelone(token, destory_token_helper);
}

void	destroy_token_list(t_token_list *token_list)
{
	ft_lstclear(&token_list, destory_token_helper);
}
