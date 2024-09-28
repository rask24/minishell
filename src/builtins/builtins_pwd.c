/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:40:19 by yliu              #+#    #+#             */
/*   Updated: 2024/09/28 14:29:56 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtins_pwd(char **args, t_ctx *ctx)
{
	char	*buf;

	(void)args;
	(void)ctx;
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		print_error("builtins_pwd", "getcwd error");
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(buf, STDOUT_FILENO);
	free(buf);
	return (EXIT_SUCCESS);
}
