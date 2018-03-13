/*
** bcopy.c
**
** bcopy function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/01/22 by Juillard Jean-Baptiste
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

void	bcopy(const void *s1, void *s2, size_t n)
{
	register size_t			offset;
	register unsigned char	*p1;
	register unsigned char	*p2;
	register size_t			i;

	if (!s1 || !s2 || !n || n > SIZE_MAX)
	{
		errno = EINVAL;
		return ;
	}
	errno ^= errno;
	p1 = (unsigned char *)(s1);
	p2 = (unsigned char *)(s2);
	i = n;
	if (p2 == p1)
		return ;
	else if (p2 > p1)
		offset = n - 1;
	else
		offset ^= offset;
	while (i)
	{
		*(p2 + offset) = *(p1 + offset);
		if (p2 > p1)
			offset--;
		else
			offset++;
		i--;
	}
}
