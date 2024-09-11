/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:08:45 by yliu              #+#    #+#             */
/*   Updated: 2024/09/10 23:34:33 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	destroy_env_helper(void *content)
{
	free(((t_env *)content)->name);
	free(((t_env *)content)->value);
	free(content);
}

void	destroy_env(t_env_list *env)
{
	ft_lstdelone(env, destroy_env_helper);
}

void	destroy_env_list(t_env_list *env_list)
{
	ft_lstclear(&env_list, destroy_env_helper);
}
