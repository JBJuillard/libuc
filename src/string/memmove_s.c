/*
** memmove_s.c
**
** memmove_s function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/01/21 by Juillard Jean-Baptiste
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

#define __STDC_WANT_LIB_EXT1__		1

#include <libuc/stddef.h>
#include <libuc/stdint.h>
#include <libuc/errno.h>

errno_t	memmove_s(void *s1, rsize_t s1max, const void *s2, rsize_t n)
{
	register size_t	offset;

	offset ^= offset;
	if (!s1 || !s2 || !s1max || s1max > RSIZE_MAX
		|| !n || n > RSIZE_MAX || n > s1max)
	{
		if (s1 && s1max && s1max <= RSIZE_MAX)
			while (offset < s1max)
				*((char *)(s1 + offset++)) = '\0';
		errno = EINVAL;
		return ((errno_t)(EINVAL));
	}
	errno ^= errno;
	if (s1 == (void *)(s2))
		return (0);
	if (s1 > (void *)(s2))
		offset = n - 1;
	while (n--)
	{
		*((char *)(s1 + offset)) = *((char *)(s2 + offset));
		if (s1 > (void *)(s2))
			offset--;
		else
			offset++;
	}
	return ((errno_t)(0));
}
