/*
** memmove_s.c
**
** memmove_s function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/01/21 by Juillard Jean-Baptiste
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

#define __STDC_WANT_LIB_EXT1__		1

#include <libuc/stddef.h>
#include <libuc/stdint.h>
#include <libuc/errno.h>

errno_t	memmove_s(void *s1, rsize_t s1max, const void *s2, rsize_t n)
{
	register unsigned char			*p1;
	register const unsigned char	*p2;
	register rsize_t				c;

	if (!s1 || !s2
		|| !s1max || s1max > RSIZE_MAX
		|| !n || n > RSIZE_MAX || n > s1max)
	{
		if (s1 && s1max && s1max <= RSIZE_MAX)
			while (s1max--)
				*((unsigned char *)(s1++)) = '\0';
		errno = EINVAL;
		return ((errno_t)(EINVAL));
	}
	errno = 0;
	p1 = (unsigned char *)(s1);
	p2 = (const unsigned char *)(s2);
	c = n;
	if (p1 == (unsigned char *)(p2))
		return (0);
	else if (p1 > (unsigned char *)(p2))
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
	return ((errno_t)(0));
}
