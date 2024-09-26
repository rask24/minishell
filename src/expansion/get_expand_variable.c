/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expand_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:59:05 by yliu              #+#    #+#             */
/*   Updated: 2024/09/26 21:29:31 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_internal.h"

static bool	is_identifier_char(char c)
{
	return (c && (ft_isalnum(c) || c == '_'));
}

char	*get_expanded_variable(t_expand_info *expand_info, t_builtins_ctx *ctx)
{
	char	*candidate_key;
	char	*value;
	char	*result;

	expand_info->consume_char(expand_info);
	if (!*expand_info->right)
		return (ft_xstrdup("$"));
	while (is_identifier_char(*expand_info->right))
		expand_info->right++;
	candidate_key = expand_info->trim(expand_info);
	if (!is_identifier(candidate_key))
		return (ft_xstrdup(""));
	value = lookup_value(candidate_key, ctx->env);
	if (!value)
		return (ft_xstrdup(""));
	result = ft_xstrdup(value);
	free(candidate_key);
	return (result);
}
