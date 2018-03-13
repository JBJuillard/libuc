/*
** strlcat.c
**
** strlcat function of Undefined-C library
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

#include <libuc/stddef.h>
#include <libuc/stdint.h>
#include <libuc/errno.h>
#include <libuc/string.h>

size_t	strlcat(char *s1, const char *s2, size_t size)
{
	register size_t	offset;

	if (!s1 || !s2 || !size || size > SIZE_MAX)
	{
		errno = EINVAL;
		return ((size_t)(0));
	}
	errno ^= errno;
	offset ^= offset;
	while (*(s1 + offset))
	{
		if (offset == SIZE_MAX)
		{
			errno = EOVERFLOW;
			return ((size_t)(0));
		}
		offset++;
	}
	if (offset >= (size - 1))
		return (size);
	while (*s2 && offset < (size - 1))
		*(s1 + offset++) = *(s2++);
	*(s1 + offset) = '\0';
	if (*s2)
		return (size + strlen(s2));
	return (offset);
}
