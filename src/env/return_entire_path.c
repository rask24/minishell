/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_entire_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:43:11 by yliu              #+#    #+#             */
/*   Updated: 2024/09/10 16:51:36 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static bool	is_basename_has_slash(const char *basename)
{
	return (ft_strchr(basename, '/'));
}

static const char	*search_path_list(const char **envp)
{
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", ft_strlen("PATH=")))
			return (*envp);
		envp++;
	}
	return (NULL);
}

static const char	*_join_dir_base(char **dirname_list, const char *basename)
{
	const char	*entire_path;

	while (*dirname_list)
	{
		entire_path = ft_strjoin(*dirname_list, ft_strjoin("/", basename));
		if (access(entire_path, F_OK) == 0)
		{
			xaccess_is_x_ok(entire_path);
			return (entire_path);
		}
		free((void *)entire_path);
		dirname_list++;
	}
	xaccess_is_f_ok_alt(basename);
	xaccess_is_x_ok(basename);
	return (ft_strjoin("./", basename));
}

const char	*return_entire_path(const char *basename, t_env_list *env_list)
{
	const char	*path_list;
	char		**dirname_list;
	const char	*absolute_path;
	const char	**alt_envp;

	(void)dirname_list;
	if (is_basename_has_slash(basename))
	{
		xaccess_is_f_ok(basename);
		xaccess_is_x_ok(basename);
		return (basename);
	}
	alt_envp = convert_env_to_array(env_list);
	path_list = search_path_list(alt_envp);
	if (!path_list)
	{
		print_error(basename, "no such file or directory");
		return (NULL);
	}
	dirname_list = ft_split(path_list + ft_strlen("PATH="), ':');
	ft_free_strs((char **)alt_envp);
	absolute_path = _join_dir_base(dirname_list, basename);
	ft_free_strs(dirname_list);
	return (absolute_path);
}
