#include "minitalk.h"

static volatile sig_atomic_t	g_ack;

static void	ack_handler(int sig)
{
	if (sig == ACK_SIG)
		g_ack = 1;
}

static void	send_bit(pid_t server_pid, int bit)
{
	g_ack = 0;
	if (kill(server_pid, (bit == 1) * BIT_1 + (bit == 0) * BIT_0) == -1)
		exit(1);
	while (!g_ack)
		pause();
}

static void	send_char(pid_t server_pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		send_bit(server_pid, (c >> i) & 1);
		i--;
	}
}

static void	send_str(pid_t server_pid, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		send_char(server_pid, (unsigned char)s[i]);
		i++;
	}
	send_char(server_pid, '\0');
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	pid_t				server_pid;

	if (argc != 3)
		return (write(2, "Usage: ./client <PID> <message>\n", 32), 1);
	server_pid = parse_pid(argv[1]);
	if (server_pid == (pid_t)-1)
		return (write(2, "Error: invalid PID\n", 19), 1);
	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(ACK_SIG, &sa, NULL);
	send_str(server_pid, argv[2]);
	return (0);
}
