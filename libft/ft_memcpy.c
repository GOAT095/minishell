/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:22:09 by hchorfi           #+#    #+#             */
/*   Updated: 2019/10/24 16:52:22 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char			*d;
	char			*s;
	unsigned int	i;

	d = (char *)dst;
	s = (char *)src;
	i = 0;
	while (i < n && (d || s))
	{
		d[i] = s[i];
		i++;
	}
	return ((void *)d);
}
