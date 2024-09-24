/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:15:45 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/24 16:09:09 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "ast.h"
#include "exec_internal.h"
#include "utils.h"

#define PIPE_IN 0
#define PIPE_OUT 1

int	execute_pipeline(t_ast *node, t_env_list *env_list, t_pipeline_conf *info)
{
	(void)node;
	(void)env_list;
	(void)info;
	return (EXIT_SUCCESS);
}
