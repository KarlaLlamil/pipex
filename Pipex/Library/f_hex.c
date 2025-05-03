/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_hex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:50:28 by karlarod          #+#    #+#             */
/*   Updated: 2025/03/14 16:00:19 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_toupper(char *str)
{
	while (*str)
	{
		if (*str >= 'a' && *str <= 'z')
		{
			*str = (*str - 32);
		}
		++str;
	}
}

static void	f_rgth(int buff, int len, unsigned long nmb, t_fmt_spcfy *format)
{
	int				count;
	unsigned long	n;

	count = buff;
	while (count > buff - len)
	{
		--count;
		n = nmb % 16;
		nmb = nmb / 16;
		if (n <= 9)
			format->args_to_str[count] = n + '0';
		else
			format->args_to_str[count] = (n % 10 + 'a');
	}
	if (format->hxa == 'p'
		|| (format->flags[2] == '#' && format->flags[1] != '0'))
	{
		format->args_to_str[count - 1] = 'x';
		format->args_to_str[count - 2] = '0';
	}
	else if (format->flags[2] == '#' && format->flags[1] == '0')
	{
		format->args_to_str[1] = 'x';
		format->args_to_str[0] = '0';
	}
}

static void	f_lfth(int len, unsigned long nmb, t_fmt_spcfy *format)
{
	int				count;
	unsigned long	n;

	n = nmb;
	if (format->hxa == 'p' || format->flags[2] == '#' )
	{
		format->args_to_str[1] = 'x';
		format->args_to_str[0] = '0';
		len += 2;
		count = 2;
	}
	else
		count = 0;
	while (len > count)
	{
		--len;
		n = nmb % 16;
		nmb = nmb / 16;
		if (n <= 9)
			format->args_to_str[len] = n + '0';
		else
			format->args_to_str[len] = (n % 10 + 'a');
	}
}

static void	f_wrt_hx(int buff, int len, unsigned long nmb, t_fmt_spcfy *format)
{
	if (format->flags[3] == '.' || format->flags[1] != '0'
		|| format->hxa == 'p')
		format->args_to_str = (char *)f_new_str(buff, ' ');
	else
		format->args_to_str = (char *)f_new_str(buff, '0');
	if (format->args_to_str != NULL)
	{
		if (format->flags[1] != '-')
			f_rgth(buff, len, nmb, format);
		else if (format->flags[1] == '-')
			f_lfth(len, nmb, format);
		if (format->hxa == 'X')
			ft_toupper(format->args_to_str);
		write(1, format->args_to_str, buff);
		free(format->args_to_str);
	}
}

void	f_hex(unsigned long nmb, char c, t_fmt_spcfy *format, int *counter)
{
	int		len;
	int		buff;

	format->hxa = c;
	len = ft_hex_len(nmb);
	if (nmb == 0)
		format->flags[2] = 'A';
	if (c == 'p' && nmb == 0)
	{
		ft_ptstr((char *)(&"(nil)"), format, counter);
		return ;
	}
	if ((format->prcn > len && c != 'p')
		|| (nmb == 0 && format->flags[3] == '.' && format->prcn <= 0))
		len = format->prcn;
	if ((format->width > len && c != 'p' && format->flags[2] != '#')
		|| (format->width > len +2 && (c == 'p' || format->flags[2] == '#')))
		buff = format->width;
	else if ((c == 'p' || format->flags[2] == '#') && len > 0)
		buff = len + 2;
	else
		buff = len;
	if (buff > 0)
		f_wrt_hx(buff, len, nmb, format);
	*counter = *counter + buff;
}
