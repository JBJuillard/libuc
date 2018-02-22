/*
** memcpy_s function for Undefined-C library
**
** Created: 01/11/2018 by Juillard Jean-Baptiste
** Updated: 01/21/2018 by Juillard Jean-Baptiste
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

errno_t	memcpy_s(void *s1, rsize_t s1max, const void *s2, rsize_t n)
{
	register size_t	offset;

	if (!s1 || !s2 || !s1max || s1max > RSIZE_MAX
		|| !n || n > RSIZE_MAX || n > s1max)
	{
		offset ^= offset;
		if (s1 && s1max && s1max <= RSIZE_MAX)
			while (offset < s1max)
				*((char *)(s1 + offset++)) = '\0';
		errno = EINVAL;
		return ((errno_t)(EINVAL));
	}
	errno ^= errno;
	offset ^= offset;
	while (offset < n)
	{
		*((char *)(s1 + offset)) = *((char *)(s2 + offset));
		offset++;
	}
	return ((errno_t)(0));
}
