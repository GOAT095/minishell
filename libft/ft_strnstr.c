/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 21:06:33 by hchorfi           #+#    #+#             */
/*   Updated: 2019/10/25 01:04:34 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t			i;
	size_t			j;
	unsigned char	*h1;
	unsigned char	*n1;

	h1 = (unsigned char *)h;
	n1 = (unsigned char *)n;
	i = 0;
	if (len == 0 && h == 0 && n)
		return (NULL);
	if (n1[i] == '\0')
		return ((char *)h1);
	while (h1[i] != '\0' && i < len)
	{
		j = 0;
		while (h1[i + j] == n1[j] && i + j < len)
		{
			if (n1[j + 1] == '\0')
				return ((char *)(&h1[i]));
			j++;
		}
		i++;
	}
	return (0);
}
