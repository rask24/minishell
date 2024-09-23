/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:40:19 by yliu              #+#    #+#             */
/*   Updated: 2024/09/05 16:20:58 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtins_pwd(char **args, char **env)
{
	char	*buf;

	(void)args;
	(void)env;
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
