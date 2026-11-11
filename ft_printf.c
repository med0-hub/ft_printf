/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelarab <mbelarab@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 08:54:47 by mbelarab          #+#    #+#             */
/*   Updated: 2026/11/11 08:47:24 by mbelarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
    va_list	args;

    i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
    {
		if(format[i] == '%' && format[i + 1] == 'c')
		{
			count += ft_putchar(va_arg(args, int));
			i += 2;
		}
		else if(format[i] == '%' && (format[i + 1] == 'd' || format[i + 1] == 'i'))
		{
			count += ft_putnbr(va_arg(args, int));
			i += 2;
		}
		else if(format[i] == '%' && format[i + 1] == 's')
		{
			count += ft_putstr(va_arg(args, char *));
			i += 2;
		}
		else if(format[i] == '%' && format[i + 1] == 'u')
		{
			count += ft_putnbr_base(va_arg(args, unsigned int), "0123456789");
			i += 2;
		}
		else if(format[i] == '%' && format[i + 1] == 'x')
		{
			count += ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef");
			i += 2;
		}
		else if(format[i] == '%' && format[i + 1] == 'X')
		{
			count += ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF");
			i += 2;
		}
		else if(format[i] == '%' && format[i + 1] == 'p')
		{
			count += ft_putadrs(va_arg(args, void *));
			i += 2;
		}
		else
		{
			count += write(1, &format[i], 1);
			i++;
		}
	}
	va_end(args);
	return (count);
}
