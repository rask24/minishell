/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:44:57 by yliu              #+#    #+#             */
/*   Updated: 2024/09/22 21:35:04 by yliu             ###   ########.fr       */
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

typedef struct s_builtins_ctx
{
	char		*cwd;
	t_env_list	*env;
	int			exit_status;
}				t_builtins_ctx;

int				builtins_cd(char **args, t_builtins_ctx *config);
int				builtins_echo(char **args, char **env);
int				builtins_env(char **args, t_builtins_ctx *config);
int				builtins_exit(char **args, t_builtins_ctx *config);
int				builtins_export(char **args, t_builtins_ctx *config);
int				builtins_pwd(char **args, char **env);
int				builtins_unset(char **args, t_builtins_ctx *config);

// export utils
void			print_a_export(void *content);
bool			cmp_func(t_env_list *a, t_env_list *b);
void			update_env_value(t_env_list *env, char *value);
t_env_list		*is_already_exist(char *key, t_env_list *env);

#endif
