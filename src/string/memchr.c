/*
** memchr.c
**
** memchr function of Undefined-C library
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
#include <stdlib.h>

void	*memchr(const void *s, int c, size_t n)
{
	register unsigned char	*ptr;

	if (!(ptr = (unsigned char *)(s))
		|| c < 0x00 || c > 0xFF || !n || n > SIZE_MAX)
	{
		errno = EINVAL;
		return (NULL);
	}
	errno ^= errno;
	s += n;
	while (ptr < (unsigned char *)(s))
	{
		if (*ptr == (unsigned char)(c))
			return ((void *)(ptr));
		ptr++;
	}
	return (NULL);
}
