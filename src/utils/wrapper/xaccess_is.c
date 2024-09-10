/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xaccess_is.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:07:06 by yliu              #+#    #+#             */
/*   Updated: 2024/09/10 16:06:59 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	xaccess_is_f_ok(const char *name)
{
	if (access(name, F_OK))
	{
		print_error("access", strerror(ENOENT));
		exit(NO_FILE_OR_CMD_ERR);
	}
	return (true);
}

bool	xaccess_is_f_ok_alt(const char *name)
{
	if (access(name, F_OK))
	{
		print_error("access", CMD_NOT_FOUND);
		exit(NO_FILE_OR_CMD_ERR);
	}
	return (true);
}

bool	xaccess_is_x_ok(const char *name)
{
	if (access(name, X_OK))
	{
		print_error("access", strerror(EACCES));
		exit(NOT_EXECUTABLE);
	}
	return (true);
}
