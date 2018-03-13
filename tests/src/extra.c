/*
** extra.c
**
** extra function for unit tests of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/01/28 by Juillard Jean-Baptiste
** Updated: 2018/03/12 by Juillard Jean-Baptiste
**
** This file is a part free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License as
** published by the Free Software Foundation; either version 3, or
** (at your option) any later version.
**
** There is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; see the file LICENSE.  If not, write to
** the Free Software Foundation, Inc., 51 Franklin Street, Fifth
** Floor, Boston, MA 02110-1301, USA.
*/

#include <libuc/stddef.h>
#include <stdlib.h>			/* Dev: a modifier après implantation de malloc et de free */
#include <libuc/errno.h>
#include <libuc/stdint.h>
#include <libuc/limits.h>
#include <stdio.h>			/* Dev: a modifier après implantation de printf */
#include <libuc/stdlst.h>

int	get_int(char *str)
{
	unsigned int	n;
	unsigned int	c;
	int				neg;
	int				loop;

	errno = 0;
	n = 0;
	neg = 0;
	loop = 0;
	while (*str < '0' || *str > '9')
	{
		if (*str == '+' && neg <= 0)
			neg--;
		else if (*str == '-' && neg >= 0)
			neg++;
		else
		{
			errno = EINVAL;
			return (0);
		}
		str++;
	}
	while (*str && (*str >= '0' || *str <= '9') && ++loop)
	{
		c = (unsigned int)((char)(*(str++) - '0'));
		if ((((n * 10U) + c) > (unsigned int)(INT_MAX) && neg <= 0)
			|| (((n * 10U) + c) > (unsigned int)(-((long long )(INT_MIN)))
				&& neg > 0))
		{
			errno = EOVERFLOW;
			return (0);
		}
		n = (n * 10U) + c;
	}
	if (!loop)
	{
		errno = EINVAL;
		return (0);
	}
	if (neg > 0)
		return ((int)(-((long long)(n))));
	return ((int)(n));
}

void	_ofree(void *key, size_t size)
{
	size_t	offset;

	if (!key || !size || size > SIZE_MAX)
	{
		errno = EINVAL;
		return ;
	}
	offset = 0;
	while (offset < size)
		*((unsigned char *)(key + offset++)) = 0x0;
	free(key);
}

int	_ocmp(const void *k1, const size_t s1, const void *k2, const size_t s2)
{
	size_t	offset;
	
	if (!k1 || !s1 || s1 > SIZE_MAX || !k2 || !s2 || s2 > SIZE_MAX)
	{
		errno = EINVAL;
		return (0);
	}
	offset = 0;
	if (s1 < s2)
		return (-((int)(*((unsigned char *)(k2 + s1)))));
	else if (s1 > s2)
		return ((int)(*((unsigned char *)(k1 + s2))));
	while (offset < s1)
	{
		if (*((unsigned char *)(k1 + offset)) != *((unsigned char *)(k2 + offset)))
			return ((int)(*((unsigned char *)(k1 + offset)) - *((unsigned char *)(k2 + offset))));
		offset++;
	}
	return (0);
}

void	*_ocpy(void *key, size_t size)
{
	void	*ptr;
	size_t	offset;

	if (!key || !size || size > SIZE_MAX)
	{
		errno = EINVAL;
		return (NULL);
	}
	if ((ptr = malloc(size)) == NULL)
		return (NULL);
	offset = 0;
	while (offset < size)
	{
		*((unsigned char *)(ptr + offset)) = *((unsigned char *)(key + offset));
		offset++;
	}
	return (ptr);
}

int		_ofunc(void **key, size_t *size)
{
	size_t	offset;

	if (!key || !*key || *size != sizeof(long long))
	{
		errno = EINVAL;
		return (1);
	}
	offset = 0;
	while (offset < *size)
		*((unsigned char *)((*key) + offset++)) = 0x0;
	return (0);
}

int		_oprint(void **k, size_t *s)
{
	static size_t	i = 0;

	if (!k || !*k || !s || !*s)
	{
		errno = EINVAL;
		return (1);
	}
	printf("%zi:\t%lli\n", i, *((long long *)(*k)));
	i++;
	return (0);
}

slst_t	*_gen_slst(long long start, long long end, long long step)
{
	slst_t	*lst;
	slst_t	*tmp;

	if ((start < end && step <= 0)
		|| (start > end && step >= 0)
		|| !step)
	{
		errno = EINVAL;
		return ((slst_t *)(NULL));
	}
	errno = 0;
	lst = (slst_t *)(NULL);
	while (start <= end)
	{
		if ((tmp = (slst_t *)malloc(sizeof(sclst_t))) == (slst_t *)(NULL)
			|| (tmp->key = malloc(sizeof(long long))) == NULL)
		{
			if (tmp)
				free((void *)(tmp));
			sclst_purge(&lst, &_ofree);
			return ((slst_t *)(NULL));
		}
		*((long long *)(tmp->key)) = start;
		tmp->size = sizeof(long long);
		tmp->next = lst;
		lst = tmp;
		start += step;
	}
	return (lst);
}

sclst_t	*_gen_sclst(long long start, long long end, long long step)
{
	sclst_t	*lst;
	sclst_t	*tmp;

	if ((start < end && step <= 0)
		|| (start > end && step >= 0)
		|| !step)
	{
		errno = EINVAL;
		return ((sclst_t *)(NULL));
	}
	errno = 0;
	lst = (sclst_t *)(NULL);
	while (start <= end)
	{
		if ((tmp = (sclst_t *)malloc(sizeof(sclst_t))) == (sclst_t *)(NULL)
			|| (tmp->key = malloc(sizeof(long long))) == NULL)
		{
			sclst_purge(&lst, &_ofree);
			return ((sclst_t *)(NULL));
		}
		*((long long *)(tmp->key)) = start;
		tmp->size = sizeof(long long);
		if (lst)
		{
			tmp->next = lst->next;
			lst->next = tmp;
		}
		else
			tmp->next = tmp;
		lst = tmp;
		start += step;
	}
	return (lst);
}

char	*_gen_str(size_t size)
{
	char 			*str;
	static const char	base[2] = {'A', 'a'};
	size_t			i;

	if (!size || size > SIZE_MAX)
	{
		errno = EINVAL;
		return ((char *)(NULL));
	}
	if ((str = (char *)malloc(size)) == (char *)(NULL))
		return ((char *)(NULL));
	*(str + size) = '\0';
	size--;
	i ^= i;
	while (i < size)
	{
		*(str + i) = ((i % 26) + base[(i % 2)]);
		i++;
	}
	return (str);
}
