/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelarab <mbelarab@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 20:18:20 by mbelarab          #+#    #+#             */
/*   Updated: 2026/11/11 12:16:05 by mbelarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_puthex(unsigned long n)
{
	int		count;
	int		check;
	char	*base;

	base = "0123456789abcdef";
	count = 0;
	if (n >= 16)
	{
		check = ft_puthex(n / 16);
		if (check == -1)
			return (-1);
		count += check;
	}
	check = ft_putchar(base[n % 16]);
	if (check == -1)
		return (-1);
	count += check;
	return (count);
}

int	ft_putadrs(void *p)
{
	int	count;
	int	check;

	count = 0;
	if (p == NULL)
		return (count += ft_putstr("(nil)"));
	check = ft_putstr("0x");
	if (check == -1)
		return (-1);
	count += check;
	check = ft_puthex((unsigned long)p);
	if (check == -1)
		return (-1);
	count += check;
	return (count);
}
