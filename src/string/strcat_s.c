/*
** strcat_s.c
**
** strcat_s function of Undefined-C library
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
#include <libuc/string.h>

errno_t	strcat_s(char *s1, rsize_t s1max, const char *s2)
{
	register rsize_t	offset;

	if (!s1 || !s1max || s1max > RSIZE_MAX || !s2
		|| !(offset = s1max - (rsize_t)(strnlen_s(s1, s1max)))
		|| offset <= (rsize_t)(strnlen_s(s2, offset)))
	{
		if (s1 && s1max && s1max <= RSIZE_MAX)
			*s1 = '\0';
		errno = EINVAL;
		return ((errno_t)(EINVAL));
	}
	errno = 0;
	offset ^= offset;
	while (*(s1 + offset))
	{
		if (offset == RSIZE_MAX)
		{
			errno = EOVERFLOW;
			return ((errno_t)(EOVERFLOW));
		}
		offset++;
	}
	if (offset >= s1max)
		return ((errno_t)(0));
	while (*s2 && offset < (s1max - 1))
		*(s1 + offset++) = *(s2++);
	*(s1 + offset) = '\0';
	return ((errno_t)(0));
}
