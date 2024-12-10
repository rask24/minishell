/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:54:29 by yliu              #+#    #+#             */
/*   Updated: 2024/12/10 14:42:44 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cd_internal.h"
#include "ctx.h"
#include "env.h"

static void	process_two_dots(char **original_path, char *normalized_path,
								char **cursor)
{
	if (*cursor - 1 != normalized_path)
	{
		(*cursor)--;
		(*cursor)--;
		while ((*cursor) > normalized_path && **cursor != '/')
			(*cursor)--;
		(*cursor)++;
	}
	*original_path += 3;
}

static void	process_slashes(char **original_path, char **cursor)
{
	while (*(*original_path + 1) == '/')
		(*original_path)++;
	**cursor = **original_path;
	(*original_path)++;
	(*cursor)++;
}

static void	process_normal_segment(char **original_path, char **cursor)
{
	while (**original_path != '\0' && **original_path != '/')
	{
		**cursor = **original_path;
		(*original_path)++;
		(*cursor)++;
	}
}

char	*normalize_path(char *original_path)
{
	char	*normalized_path;
	char	*cursor;

	normalized_path = ft_xmalloc(sizeof(char) * ft_strlen(original_path) + 1);
	cursor = normalized_path;
	while (*original_path != '\0')
	{
		if (ft_strncmp(original_path, "./", 2) == 0)
			original_path += 2;
		else if (ft_strncmp(original_path, "../", 3) == 0)
			process_two_dots(&original_path, normalized_path, &cursor);
		else if (*original_path == '/')
			process_slashes(&original_path, &cursor);
		else
			process_normal_segment(&original_path, &cursor);
	}
	*cursor = '\0';
	return (normalized_path);
}

void	update_env_pwd(t_ctx *ctx)
{
	t_env_list	*env_pwd;

	env_pwd = lookup_env("PWD", ctx->env);
	if (env_pwd == NULL)
	{
		env_pwd = construct_env(ft_xstrdup("PWD"), ft_xstrdup(ctx->cwd));
		ft_lstadd_back(&ctx->env, env_pwd);
	}
	else
		update_env_value(env_pwd, ft_xstrdup(ctx->cwd));
}
