/*
ideia: comunicação entre processos via sinais

SIGUSR1 = 0
SIGUSR2 = 1

abordagem:
Receber bit a bit e ir montando o caractere. Quando receber 8 bits, montar o caractere e imprimir.

abordagem de recebimento: (bit 7 → bit 0)

---
kill() = envia o cutucão
sigaction() = define como eu reajo quando eu for cutucado
SA_SIGINFO = me diz quem me cutucou
*/

#include "minitalk.h"

/*
Passo 2) Criar um handler “de teste”

No server.c, crie uma função handler com assinatura de sigaction (3 parâmetros):
int sig
siginfo_t *info
void *context

Dentro dele:
ignore info e context por enquanto
faça um write(1, "1", 1) se sig == SIGUSR1
faça um write(1, "2", 1) se sig == SIGUSR2

Objetivo: provar que o server realmente recebe sinais.
*/
static void	handler(int sig, siginfo_t *info, void *ctx)
{
	static unsigned char	byte;
	static int				bit_count;
	int						bit;

	(void)ctx;

	/* define o bit do sinal */
	bit = 0;
	if (sig == BIT_1)
		bit = 1;

	/* acumula no byte (bit 7 -> bit 0) */
	byte = (byte << 1) | bit;
	bit_count++;

	/* fechou 8 bits = 1 char */
	if (bit_count == 8)
	{
		if (byte == '\0')
			write(1, "\n", 1);
		else
			write(1, &byte, 1);
		byte = 0;
		bit_count = 0;
	}
	if (info)
		kill(info->si_pid, ACK_SIG); /* confirma recebimento */
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	// pega o pid do server
	pid = getpid();

	/* (temporario) mostra que o server subiu */
	write(1, "PID: ", 5);

	// printa o PID;
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);

	/* define qual funcao vai rodar quando o sinal chegar */
	sa.sa_sigaction = handler;

	/* habilita receber info extra do sinal (ex: PID de quem enviou) */
	sa.sa_flags = SA_SIGINFO;

	/* inicializa a mascara de sinais (padrao: nao bloquear nada extra) */
	sigemptyset(&sa.sa_mask);

	/* liga o handler para BIT_0 e BIT_1 */
	sigaction(BIT_0, &sa, NULL);
	sigaction(BIT_1, &sa, NULL);

	/* fica esperando sinais para sempre */
	while (1)
		pause();
}
