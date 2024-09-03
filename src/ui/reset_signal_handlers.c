/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_signal_handlers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:03:51 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/03 17:52:48 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

#include "utils.h"

void	reset_signal_handlers(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		print_error("signal", strerror(errno));
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		print_error("signal", strerror(errno));
}
