/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedrferr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:59:29 by pedrferr          #+#    #+#             */
/*   Updated: 2026/01/20 19:59:32 by pedrferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		write(1, "-", fd);
		nbr = -nbr;
	}
	if (nbr >= 10)
		ft_putnbr_fd((nbr / 10), fd);
	c = (nbr % 10) + '0';
	write(1, &c, fd);
}

static int	is_digits(char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

pid_t	parse_pid(char *s)
{
	long	n;
	int		i;

	if (!is_digits(s))
		return ((pid_t) - 1);
	n = 0;
	i = 0;
	while (s[i])
	{
		n = (n * 10) + (s[i] - '0');
		if (n > 2147483647)
			return ((pid_t) - 1);
		i++;
	}
	if (n <= 0)
		return ((pid_t) - 1);
	return ((pid_t)n);
}
