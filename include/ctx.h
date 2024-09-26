/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:01:26 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/25 16:02:18 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTX_H
# define CTX_H

# include "env.h"

typedef struct s_ctx
{
	char		*cwd;
	t_env_list	*env;
	int			exit_status;
}				t_ctx;

#endif
