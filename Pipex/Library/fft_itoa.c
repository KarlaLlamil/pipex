/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fft_itoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:40:20 by karlarod          #+#    #+#             */
/*   Updated: 2025/04/10 17:15:19 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	f_rgt(int len, int buff, unsigned int numb, t_fmt_spcfy *format)
{
	int	count;

	count = buff;
	while (count > buff - len)
	{
		--count;
		format->args_to_str[count] = (numb % 10 + '0');
		numb = numb / 10;
	}
	if (format->flags[0] != 'A' && format->flags[1] != '0')
		format->args_to_str[count - 1] = format->flags[0];
	else if (format->flags[0] != 'A' && format->flags[1] == '0')
		format->args_to_str[0] = format->flags[0];
}

static void	f_lft(int len, unsigned int numb, t_fmt_spcfy *format)
{
	int		count;

	count = 0;
	if (format->flags[0] != 'A')
	{
		format->args_to_str[0] = format->flags[0];
		++ len;
		count = 1;
	}
	else
		count = 0;
	while (len > count)
	{
		--len;
		format->args_to_str[len] = (numb % 10 + '0');
		numb = numb / 10;
	}
}

static void	f_wrt_n(int buff, int len, unsigned int n, t_fmt_spcfy *format)
{
	if (format->flags[3] == '.' || format->flags[1] != '0')
		format->args_to_str = (char *)f_new_str(buff, ' ');
	else
		format->args_to_str = (char *)f_new_str(buff, '0');
	if (format->args_to_str != NULL)
	{
		if (format->flags[1] != '-')
			f_rgt(len, buff, n, format);
		else if (format->flags[1] == '-')
			f_lft(len, n, format);
		write(1, format->args_to_str, buff);
		free(format->args_to_str);
	}
}

void	ft_utoa(unsigned int n, t_fmt_spcfy *format, int *counter)
{
	int				len;
	unsigned int	numb;
	int				buff;

	len = 0;
	numb = n;
	if (n == 0)
		len = 1;
	while (n > 0)
	{
		++len;
		n = n / 10;
	}
	if (format->prcn > len
		|| (numb == 0 && format->flags[3] == '.' && format->prcn <= 0))
		len = format->prcn;
	if (format->width > len)
		buff = format->width;
	else
		buff = len;
	format->flags[0] = 'A';
	f_wrt_n(buff, len, numb, format);
	*counter += buff;
}

void	fft_itoa(int n, t_fmt_spcfy *format, int *counter)
{
	long		numb;
	int			buff;
	int			len;

	numb = n;
	len = ft_int_len(numb);
	if (n < 0)
	{
		format->flags[0] = '-';
		numb = -1 * n;
	}
	if (format->prcn > len
		|| (n == 0 && format->flags[3] == '.' && format->prcn <= 0))
		len = format->prcn;
	if ((format->width > len && format->flags[0] == 'A')
		|| (format->width > len + 1 && format->flags[0] != 'A'))
		buff = format->width;
	else if (format->flags[0] != 'A')
		buff = len + 1;
	else
		buff = len;
	f_wrt_n(buff, len, numb, format);
	*counter += buff;
}
