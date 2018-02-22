/*
** bcopy function for Undefined-C library
**
** Created: 01/22/2018 by Juillard Jean-Baptiste
** Updated: 01/24/2018 by Juillard Jean-Baptiste
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

void	bcopy(const void *s1, void *s2, size_t n)
{
	register size_t	offset;

	if (!s1 || !s2 || !n || n > SIZE_MAX)
	{
		errno = EINVAL;
		return ;
	}
	errno ^= errno;
	if (s2 == (void *)(s1))
		return ;
	if (s2 > (void *)(s1))
		offset = n - 1;
	else
		offset ^= offset;
	while (n--)
	{
		*((char *)(s2 + offset)) = *((char *)(s1 + offset));
		if (s2 > (void *)(s1))
			offset--;
		else
			offset++;
	}
}
