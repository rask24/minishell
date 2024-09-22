/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_cmd_args_to_array.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:50:40 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/22 11:52:49 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

char	**convert_cmd_args_to_array(t_ast *node)
{
	t_list	*cmd_args;
	char	**argv;
	int		i;

	cmd_args = node->cmd_args;
	argv = ft_xmalloc(sizeof(char *) * (ft_lstsize(cmd_args) + 1));
	i = 0;
	while (cmd_args != NULL)
	{
		argv[i] = cmd_args->content;
		cmd_args = cmd_args->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
