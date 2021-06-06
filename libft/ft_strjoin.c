/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:39:52 by hchorfi           #+#    #+#             */
/*   Updated: 2019/10/21 22:21:50 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		l1;
	int		l2;
	char	*strjoin;

	if (!s1 || !s2)
		return (0);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	strjoin = malloc((l1 + l2 + 1) * sizeof(char));
	l1 = -1;
	l2 = 0;
	while (s1[++l1] != '\0')
		strjoin[l1] = s1[l1];
	while (s2[l2] != '\0')
		strjoin[l1++] = s2[l2++];
	strjoin[l1] = '\0';
	return (strjoin);
}
