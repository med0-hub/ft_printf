/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelarab <mbelarab@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:17:29 by mbelarab          #+#    #+#             */
/*   Updated: 2026/11/11 12:12:24 by mbelarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	long	nb;
	int		count;
	int		check;

	nb = n;
	count = 0;
	if (nb < 0)
	{
		nb = -nb;
		count += ft_putchar('-');
		if (count == -1)
			return (-1);
	}
	if (nb > 9)
	{
		check = ft_putnbr(nb / 10);
		if (check == -1)
			return (-1);
		count += check;
	}
	check = ft_putchar((nb % 10) + '0');
	if (check == -1)
		return (-1);
	count += check;
	return (count);
}
