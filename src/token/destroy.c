/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:40:41 by yliu              #+#    #+#             */
/*   Updated: 2024/08/19 13:28:17 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "token.h"

void	destroy_token(t_token *token)
{
	free(token->value);
	free(token);
}

static void	destroy_token_wrapper(void *token)
{
	destroy_token((t_token *)token);
}

void	destroy_token_list(t_token_list *token_list)
{
	ft_lstclear(&token_list, destroy_token_wrapper);
}
