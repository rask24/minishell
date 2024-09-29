/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:40:19 by yliu              #+#    #+#             */
/*   Updated: 2024/09/29 16:32:35 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtins_pwd(char **args, t_ctx *ctx)
{
	(void)args;
	ft_putendl_fd(ctx->cwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
