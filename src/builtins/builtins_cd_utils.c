/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:54:29 by yliu              #+#    #+#             */
/*   Updated: 2024/10/05 19:36:04 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cd_internal.h"

static void trim_one_dot(t_string *path_info, char **ans)
{
	char	*tmp;

	tmp = trim(path_info);
	*ans = ft_xstrjoin2(*ans, tmp);
	free(tmp);
	consume_char(path_info);
	consume_char(path_info);
}

char	*remove_long_path(char *path)
{
	char			*ans;
	char *tmp;
	t_string	*path_info;

	ans = NULL;
	path_info = construct_string_struct(path);
	while (*path_info->right)
	{
		if (ft_strncmp(path_info->right, "./", 2) == 0)
			trim_one_dot(path_info, &ans);
		else
			path_info->right++;
	}
	tmp = trim(path_info);
	ans = ft_xstrjoin2(ans,tmp);
	free(tmp);
	destroy_string_struct(path_info);
	return (ans);
}
