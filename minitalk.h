/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedrferr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:59:56 by pedrferr          #+#    #+#             */
/*   Updated: 2026/01/20 20:00:00 by pedrferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>

# define BIT_0 SIGUSR1
# define BIT_1 SIGUSR2
# define ACK_SIG SIGUSR2

void	ft_putnbr_fd(int n, int fd);
pid_t	parse_pid(char *s);

#endif
