/*
** memmove.c
**
** memmove function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/01/11 by Juillard Jean-Baptiste
** Updated: 2018/04/15 by Juillard Jean-Baptiste
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
#include <libuc/stdint.h>
#include <libuc/errno.h>
#include <libuc/stdlib.h>

void	*memmove(void *s1, const void *s2, size_t n)
{
	register unsigned char			*p1;
	register const unsigned char	*p2;
	register size_t					c;

	if (!(p1 = (unsigned char *)(s1))
		|| !(p2 = (const unsigned char *)(s2))
		|| !n || n > SIZE_MAX)
	{
		errno = EINVAL;
		return (NULL);
	}
	errno = 0;
	c = n;
	if (p1 == p2)
		return (s1);
	else if (p1 > p2)
	{
		p1 += c - 1;
		p2 += c - 1;
		while (c)
		{
			*(p1--) = *((unsigned char *)(p2--));
			--c;
		}
	}
	else
	{
		while (c)
		{
			*(p1++) = *((unsigned char *)(p2++));
			--c;
		}
	}
	return (s1);
}
