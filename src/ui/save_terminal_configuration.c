/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_terminal_configuration.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:34:50 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/03 17:55:23 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "utils.h"

void	save_terminal_configuration(struct termios *original_termios)
{
	if (tcgetattr(STDIN_FILENO, original_termios) == -1)
		print_error("tcgetattr", strerror(errno));
}
