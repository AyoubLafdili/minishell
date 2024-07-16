/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezahiri <ezahiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:29:43 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/16 22:49:39 by ezahiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*constr;
	int		flen;
	int		slen;

	if (!s1)
		return (ft_strdup(s2));
	flen = ft_strlen(s1);
	slen = ft_strlen(s2);
	constr = (char *) ft_malloc((flen + slen + 1) * sizeof(char), 1);
	if (constr == NULL)
		return (NULL);
	ft_strlcpy (constr, s1, flen + 1);
	ft_strlcat (constr, s2, (flen + slen + 1));
	return (constr);
}
