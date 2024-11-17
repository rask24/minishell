/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_expanded_variable.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:59:05 by yliu              #+#    #+#             */
/*   Updated: 2024/11/17 20:08:54 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_internal.h"

static bool	is_identifier_char(char c)
{
	return (c && (ft_isalnum(c) || c == '_'));
}

static char	*resolve_env(char *candidate_key, t_env_list *env)
{
	char	*value;

	if (!is_identifier(candidate_key))
		return (ft_xstrdup(""));
	value = lookup_value(candidate_key, env);
	if (!value)
		return (ft_xstrdup(""));
	return (ft_xstrdup(value));
}

char	*trim_expanded_variable(t_string *expand_info, t_ctx *ctx)
{
	char	*candidate_key;
	char	*result;

	consume_char(expand_info);
	if (*expand_info->right == '\0'
		|| ft_strchr(" \t", *expand_info->right)
		|| *expand_info->right == '\"')
		return (ft_xstrdup("$"));
	if (*expand_info->right == '?')
	{
		consume_char(expand_info);
		return (ft_itoa(ctx->exit_status));
	}
	while (is_identifier_char(*expand_info->right))
		expand_info->right++;
	candidate_key = trim(expand_info);
	result = resolve_env(candidate_key, ctx->env);
	free(candidate_key);
	return (result);
}
