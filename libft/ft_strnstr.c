/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <apuddu@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:22:12 by apuddu            #+#    #+#             */
/*   Updated: 2024/03/23 16:19:48 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hash(const char *s, size_t len)
{
	size_t		i;
	long long	h;

	i = 0;
	h = 0;
	while (i < len)
	{
		h = (h * 256 + s[i]) % 1000000007;
		i++;
	}
	return ((int)h);
}

static int	hashroll(char l, char r, long long hash, long long pow)
{
	hash = (hash * 256) % 1000000007;
	return (((hash - l * pow + r) % 1000000007 + 1000000007) % 1000000007);
}

static int	power(int x, int e)
{
	long long	pow;

	pow = 1;
	while (e > 0)
	{
		pow = (x * pow) % 1000000007;
		e--;
	}
	return ((int)pow);
}

static size_t	ft_strnlen(const char *s, size_t n)
{
	char	*t;

	t = ft_memchr(s, 0, n);
	if (t == NULL)
		return (n);
	return (t - s);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	lil_len;
	int		h1;
	int		h2;
	int		pow;
	size_t	i;

	lil_len = ft_strlen(little);
	pow = power(256, lil_len);
	len = ft_strnlen(big, len);
	i = lil_len;
	h1 = hash(big, lil_len);
	h2 = hash(little, lil_len);
	if (h1 == h2 && ft_memcmp(little, big, lil_len) == 0)
		return ((char *)big);
	while (i < len)
	{
		h1 = hashroll(big[i - lil_len], big[i], h1, pow);
		if (h1 == h2 && ft_memcmp(little, big + i - lil_len + 1, lil_len) == 0)
			return ((char *)big + i - lil_len + 1);
		i++;
	}
	return (NULL);
}
