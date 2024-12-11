/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_internal.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:53:44 by yliu              #+#    #+#             */
/*   Updated: 2024/12/10 14:44:11 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_CD_INTERNAL_H
# define BUILTINS_CD_INTERNAL_H

# include "ctx.h"

char	*normalize_path(char *path);
void	update_env_pwd(t_ctx *ctx);

#endif
