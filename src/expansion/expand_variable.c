/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:08:50 by yliu              #+#    #+#             */
/*   Updated: 2024/09/29 11:59:19 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "expansion_internal.h"

static char	*trim_single_quotes(t_expand_info *expand_info)
{
	expand_info->right++;
	while (*expand_info->right && *expand_info->right != '\'')
		expand_info->right++;
	expand_info->right++;
	return (trim(expand_info));
}

char	*expand_variable(char *input, t_ctx *ctx)
{
	t_expand_info	*expand_info;
	char			*trimed;
	char			*expanded;

	expand_info = construct_expand_info(input);
	expanded = NULL;
	while (*expand_info->right)
	{
		if (*expand_info->right == '\'')
			trimed = trim_single_quotes(expand_info);
		else if (*expand_info->right == '$')
			trimed = trim_expanded_variable(expand_info, ctx);
		else
			trimed = trim_till(expand_info, "$\'");
		expanded = ft_xstrjoin2(expanded, trimed);
		free(trimed);
	}
	destory_expand_info(expand_info);
	return (expanded);
}
