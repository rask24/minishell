/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:58:39 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/03 18:00:26 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include <termios.h>

# define PROMPT "minishell$ "

void	init_signal_handlers(void);
void	reset_signal_handlers(void);
void	save_terminal_configuration(struct termios *original_termios);
void	restore_terminal_configuration(struct termios *original_termios);

#endif
