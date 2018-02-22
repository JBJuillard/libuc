/*
** strndupa function for Undefined-C library
**
** Created: 01/22/2018 by Juillard Jean-Baptiste
** Updated: 01/22/2018 by Juillard Jean-Baptiste
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
#include <stdlib.h>

char	*strndupa(const char *s, size_t n)
{
	register size_t	len;
	register size_t	offset;
	register char	*ptr;

	if (!s || !n || n > SIZE_MAX)
	{
		errno = EINVAL;
		return ((char *)(NULL));
	}
	errno ^= errno;
	len ^= len;
	offset ^= offset;
	while (*(s + len))
		len++;
	if (len > n)
		len = n;
	if ((ptr = (char *)alloca(len + 1)) == (char *)(NULL))
		return ((char *)(NULL));
	*(ptr + len) = '\0';
	while (offset < len)
	{
		*(ptr + offset) = *(s + offset);
		offset++;
	}
	return (ptr);
}
