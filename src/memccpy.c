/*
** memccpy function for Undefined-C library
**
** Created: 01/11/2018 by Juillard Jean-Baptiste
** Updated: 01/25/2018 by Juillard Jean-Baptiste
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

void	*memccpy(void *s1, const void *s2, int c, size_t n)
{
	register size_t	offset;

	if (!s1 || !s2 || c < 0x00 || c > 0xFF || !n || n > SIZE_MAX)
	{
		errno = EINVAL;
		return (NULL);
	}
	errno ^= errno;
	offset ^= offset;
	while (offset < n && (int)(*((char *)(s2 + offset))) != c)
	{
		*((char *)(s1 + offset)) = *((char *)(s2 + offset));
		offset++;
	}
	return (s1);
}
