/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:44:57 by yliu              #+#    #+#             */
/*   Updated: 2024/10/24 23:09:23 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "ctx.h"
# include "env.h"
# include "libft.h"
# include "utils.h"

int				builtins_cd(char **args, t_ctx *ctx);
int				builtins_echo(char **args, t_ctx *ctx);
int				builtins_env(char **args, t_ctx *ctx);
int				builtins_exit(char **args, t_ctx *ctx);
int				builtins_export(char **args, t_ctx *ctx);
int				builtins_pwd(char **args, t_ctx *ctx);
int				builtins_unset(char **args, t_ctx *ctx);

// export utils
void			print_a_export(void *content);
bool			cmp_func(t_env_list *a, t_env_list *b);
void			print_error_export(const char *input);

#endif
