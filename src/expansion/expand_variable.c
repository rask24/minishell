/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:08:50 by yliu              #+#    #+#             */
/*   Updated: 2024/09/24 15:49:31 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

typedef char	*(*t_exec_func)(char *string, int *i, t_builtins_ctx *ctx);

static char	*update_expanded(char *expanded, char *result)
{
	char	*tmp;

	if (result == NULL)
		return (expanded);
	if (expanded == NULL)
		expanded = ft_xstrdup(result);
	else
	{
		tmp = ft_xstrjoin(expanded, result);
		free(expanded);
		expanded = tmp;
	}
	return (expanded);
}

static char	*get_untill_dollar(char *string, int *i, t_builtins_ctx *ctx)
{
	char	*result;

	(void)ctx;
	while (string[*i] && string[*i] != '$')
		(*i)++;
	result = ft_xstrndup(string, *i);
	return (result);
}

static char	*get_expanded_variable(char *string, int *i, t_builtins_ctx *ctx)
{
	char	*tmp;
	char	*result;
	char	*ans;

	if (!*string)
		return (ft_xstrdup("$"));
	while (string[*i] && (ft_isalnum(string[*i]) || string[*i] == '_'))
		(*i)++;
	tmp = ft_xstrndup(string, *i);
	if (!is_identifier(tmp))
		return (ft_xstrdup(""));
	result = lookup_value(tmp, ctx->env);
	if (!result)
		return (ft_xstrdup(""));
	ans = ft_xstrdup(result);
	free(tmp);
	return (ans);
}

char	*expand_variable(char *string, t_builtins_ctx *ctx)
{
	int			len;
	t_exec_func	get_expanded_str;
	char		*result;
	char		*expanded;

	expanded = NULL;
	while (*string)
	{
		if (*string == '$')
		{
			++string;
			get_expanded_str = get_expanded_variable;
		}
		else
			get_expanded_str = get_untill_dollar;
		len = 0;
		result = get_expanded_str(string, &len, ctx);
		string += len;
		expanded = update_expanded(expanded, result);
		free(result);
	}
	return (expanded);
}
