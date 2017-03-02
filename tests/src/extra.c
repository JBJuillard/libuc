/*
** extra function for units tests of Undefined-C library
**
** Created: 28/01/2017 by Juillard Jean-Baptiste
** Updated: 28/01/2017 by Juillard Jean-Baptiste
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License as
** published by the Free Software Foundation; either version 3, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; see the file LICENSE.  If not, write to
** the Free Software Foundation, Inc., 51 Franklin Street, Fifth
** Floor, Boston, MA 02110-1301, USA.
*/

#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <limits.h>

#include "stdlst.h"

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
		if ((tmp = (slst_t *)malloc(sizeof(slst_t))) == (slst_t *)(NULL)
			|| (tmp->key = malloc(sizeof(long long))) == NULL)
		{
			slst_purge(&lst, &_ofree);
			return ((slst_t *)(NULL));
		}
		*((long long *)(tmp->key)) = start;
		tmp->size = sizeof(long long);
		tmp->next = lst;
		lst= tmp;
		start += step;
	}
	return (lst);
}

int		_ofunc(void *key, size_t size)
{
	size_t	offset;

	if (!key || size != sizeof(long long))
	{
		errno = EINVAL;
		return (0);
	}
	offset = 0;
	while (offset < size)
		*((unsigned char *)(key + offset++)) = 0x0;
	free(key);
	return (0);
}
