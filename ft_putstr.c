/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelarab <mbelarab@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:18:09 by mbelarab          #+#    #+#             */
/*   Updated: 2026/11/11 11:13:24 by mbelarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	count;
	int	check;

	if (!str)
		return (ft_putstr("(null)"));
	count = 0;
	check = 0;
	while (*str)
	{
		check = ft_putchar(*str++);
		if (check == -1)
			return (-1);
		count += check;
	}
	return (count);
}
