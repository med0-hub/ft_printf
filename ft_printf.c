/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelarab <mbelarab@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 08:54:47 by mbelarab          #+#    #+#             */
/*   Updated: 2026/11/11 16:29:04 by mbelarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_conversion(char sp, va_list args)
{
	if (sp == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (sp == 'd' || sp == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (sp == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (sp == 'u')
		return (ft_putnbr_base(va_arg(args, unsigned int), "0123456789"));
	else if (sp == 'x')
		return (ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef"));
	else if (sp == 'X')
		return (ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF"));
	else if (sp == 'p')
		return (ft_putadrs(va_arg(args, void *)));
	else if (sp == '%')
		return (ft_putchar('%'));
	return (0);
}

static int	ft_process(const char *format, int *i, va_list args)
{
	int	check;

	if (format[*i] == '%')
	{
		check = ft_conversion(format[*i + 1], args);
		*i += 2;
	}
	else
	{
		check = write(1, &format[*i], 1);
		(*i)++;
	}
	return (check);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	int		check;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		check = ft_process(format, &i, args);
		if (check == -1)
		{
			va_end(args);
			return (-1);
		}
		count += check;
	}
	va_end(args);
	return (count);
}
