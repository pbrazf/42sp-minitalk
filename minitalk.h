#ifndef MINITALK_H
#define MINITALK_H

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define BIT_0 SIGUSR1
#define BIT_1 SIGUSR2
#define ACK_SIG SIGUSR1 // AKG = Acknowledgment	Signal

void	ft_putnbr_fd(int n, int fd);

#endif /* MINITALK_H */
