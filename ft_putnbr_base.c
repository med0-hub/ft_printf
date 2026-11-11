/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelarab <mbelarab@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 16:36:30 by mbelarab          #+#    #+#             */
/*   Updated: 2026/11/11 12:12:08 by mbelarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	ft_strlen(const char *s)
{
	unsigned int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	ft_putnbr_base(unsigned int n, char *base)
{
	unsigned int	len_base;
	int				count;
	int				check;

	len_base = ft_strlen(base);
	if (len_base == 0)
		return (0);
	count = 0;
	if (n >= len_base)
	{
		check = ft_putnbr_base(n / len_base, base);
		if (check == -1)
			return (-1);
		count += check;
	}
	check = ft_putchar(base[n % len_base]);
	if (check == -1)
		return (-1);
	count += check;
	return (count);
}
