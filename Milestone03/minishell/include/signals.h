/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:46:43 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/14 12:59:14 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

extern volatile sig_atomic_t	g_signal;

// signals.c
void	setup_signals_shell(void);
void	restore_default_signals(void);
void	ignore_interactive_signals(void);

#endif
