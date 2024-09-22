/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_internal.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:59:45 by yliu              #+#    #+#             */
/*   Updated: 2024/09/22 16:36:23 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_INTERNAL_H
# define EXPANSIONS_INTERNAL_H

# include "expansions.h"

typedef struct s_expansion
{
	char	*left;
	char	*right;
}			t_expansion;

void	construct_expansions(char *input, t_expansion *expansions);
char	*get_next_section(t_expansion *expansions, t_env_list *env);
bool	is_start_of_input_(t_expansion *expansions);
char	*process_single_quote(t_expansion *expansions);
char	*process_variable(t_expansion *expansion, t_env_list *env);

#endif
