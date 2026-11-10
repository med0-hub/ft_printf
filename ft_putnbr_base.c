/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelarab <mbelarab@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 16:36:30 by mbelarab          #+#    #+#             */
/*   Updated: 2026/11/10 18:37:17 by mbelarab         ###   ########.fr       */
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

	len_base = ft_strlen(base);
	if (len_base == 0)
		return (0);
	count = 0;
	if (n >= len_base)
		count += ft_putnbr_base(n / len_base, base);
	count += ft_putchar(base[n % len_base]);
	return (count);
}
