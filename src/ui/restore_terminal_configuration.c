/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_terminal_configuration.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:38:16 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/03 17:55:30 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "utils.h"

void	restore_terminal_configuration(struct termios *original_termios)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, original_termios) == -1)
		print_error("tcsetattr", strerror(errno));
}
