/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:08:45 by yliu              #+#    #+#             */
/*   Updated: 2024/09/13 16:18:12 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	destroy_env_helper(void *content)
{
	free(((t_env *)content)->key);
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
