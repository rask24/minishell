/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:59:54 by reasuke           #+#    #+#             */
/*   Updated: 2024/12/09 20:45:45 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "env.h"
#include "libft.h"
#include "routine.h"

static t_ctx	*construct_ctx(char **envp)
{
	t_ctx	*ctx;

	ctx = ft_xmalloc(sizeof(t_ctx));
	ctx->cwd = getcwd(NULL, 0);
	ctx->env = init_env(envp, ctx->cwd);
	ctx->exit_status = EXIT_SUCCESS;
	return (ctx);
}

static void	destroy_ctx(t_ctx *ctx)
{
	free(ctx->cwd);
	free(ctx);
}

int	main(int argc, char **argv, char **envp)
{
	t_ctx	*ctx;
	int		exit_status;

	(void)argc;
	(void)argv;
	ctx = construct_ctx(envp);
	loop(ctx);
	exit_status = ctx->exit_status;
	destroy_env_list(ctx->env);
	destroy_ctx(ctx);
	return (exit_status);
}
