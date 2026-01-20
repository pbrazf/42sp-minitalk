/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedrferr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:59:00 by pedrferr          #+#    #+#             */
/*   Updated: 2026/01/20 19:59:14 by pedrferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handler(int sig, siginfo_t *info, void *ctx)
{
	static unsigned char	byte;
	static int				bit_count;
	int						bit;

	// context is not used but needed for the prototype
	(void)ctx;
	bit = 0;
	if (sig == BIT_1)
		bit = 1;
	byte = (byte << 1) | bit;
	bit_count++;
	if (bit_count == 8)
	{
		if (byte == '\0')
			write(1, "\n", 1);
		else
			write(1, &byte, 1);
		byte = 0;
		bit_count = 0;
	}
	// A signal is sent back to the client to acknowledge the reception of the bit
	if (info)
		kill(info->si_pid, ACK_SIG);
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	// Print the server PID -> getpid is a syscall that returns the process ID from unistd.h
	pid = getpid();
	write(1, "PID: ", 5);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	// Define what to do when receiving signals
	sa.sa_sigaction = handler;
	// Request for more information about the signal
	sa.sa_flags = SA_SIGINFO;
	// List of signals to be blocked during the execution of the handler - empty set
	sigemptyset(&sa.sa_mask);
	// When this signal is received, the handler function is called ( by sa config )
	sigaction(BIT_0, &sa, NULL);
	sigaction(BIT_1, &sa, NULL);
	while (1)
		pause();
}
