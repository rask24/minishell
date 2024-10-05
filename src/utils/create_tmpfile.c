/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tmpfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:42:23 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/02 19:36:37 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>

#include "utils.h"

int	create_tmpfile(char *tmp_name, size_t tmp_len, const char *target)
{
	int		fd;
	char	*dirs[5];
	char	*path;
	int		i;

	dirs[0] = "/tmp/";
	dirs[1] = "/var/tmp/";
	dirs[2] = "/usr/tmp/";
	dirs[3] = "./";
	dirs[4] = NULL;
	i = 0;
	while (dirs[i])
	{
		path = ft_xstrjoin(dirs[i], target);
		fd = open(path, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
		ft_strlcpy(tmp_name, path, tmp_len);
		free(path);
		if (fd != -1)
			break ;
		i++;
	}
	return (fd);
}
