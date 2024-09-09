/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:35:50 by yliu              #+#    #+#             */
/*   Updated: 2024/09/09 15:22:29 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdlib.h>

# include "libft.h"
# include "utils.h"

typedef struct s_env
{
	char		*name;
	char		*value;
}				t_env;

typedef t_list	t_env_list;

t_env_list		*construct_env(char *name, char *value);
void			destroy_env(t_env_list *env);
void			destroy_env_list(t_env_list *env_list);
char			*get_env_name(t_env_list *env);
char			*get_env_value(t_env_list *env);

#endif
