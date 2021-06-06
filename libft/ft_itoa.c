/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:13:46 by hchorfi           #+#    #+#             */
/*   Updated: 2019/10/24 18:43:52 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nn(unsigned int n, int i)
{
	if (n <= 9)
		i++;
	if (n >= 10)
	{
		i++;
		while (n >= 10)
		{
			i++;
			n = n / 10;
		}
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*itoa;
	int				i;
	int				len;
	unsigned int	nb;

	i = 0;
	if (n < 0)
	{
		nb = n * -1;
		i++;
	}
	else
		nb = n;
	len = ft_nn(nb, i);
	itoa = malloc(sizeof(char) * (len + 1));
	itoa[len--] = '\0';
	while (len >= i)
	{
		itoa[len--] = (nb % 10) + 48;
		nb = nb / 10;
	}
	if (n < 0)
		itoa[0] = '-';
	return (itoa);
}
