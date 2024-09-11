/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:44:57 by yliu              #+#    #+#             */
/*   Updated: 2024/09/11 13:41:26 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "env.h"
# include "libft.h"
# include "utils.h"

typedef struct s_config
{
	char			*cwd;
	t_env_list		*env;
	int				exit_status;
}					t_config;

int					builtins_echo(char **args, char **env);
int					builtins_env(char **args, t_config *config);
int					builtins_exit(char **args, t_config *config);
int					builtins_export(char **args, t_config *config);
int					builtins_pwd(char **args, char **env);
int					builtins_unset(char **args, t_config *config);

#endif
