/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:35:50 by yliu              #+#    #+#             */
/*   Updated: 2024/10/24 23:09:33 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdlib.h>
# include <unistd.h>

# include "libft.h"
# include "utils.h"

typedef struct s_env
{
	char		*key;
	bool		is_valid_value;
	char		*value;
}				t_env;

typedef t_list	t_env_list;

t_env_list		*construct_env(char *name, char *value);
t_env_list		*construct_env_with_bool(char *key, char *value,
					bool is_valid_value);
t_env_list		*convert_array_to_env(char **envp);
const char		**convert_env_to_array(t_env_list *env_list);
void			destroy_env(t_env_list *env);
void			destroy_env_helper(void *content);
void			destroy_env_list(t_env_list *env_list);
bool			get_env_is_valid_value(t_env_list *env);
char			*get_env_key(t_env_list *env);
char			*get_env_value(t_env_list *env);
t_env_list		*init_env(char **envp);
t_env_list		*lookup_env(char *key, t_env_list *env);
char			*lookup_value(const char *key, t_env_list *env_list);
const char		*return_entire_path(const char *basename, t_env_list *env_list);
void			set_env_is_valid_value(t_env_list *env, bool is_valid_value);
void			set_env_value(t_env_list *env, char *value);
void			update_env_value(t_env_list *env, char *value);

#endif
