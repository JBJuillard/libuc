/*
** ffsll.c
**
** ffsll function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/01/24 by Juillard Jean-Baptiste
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
#include <limits.h>

int	ffsll(long long int i)
{
	register unsigned long long int	mask;
	register int			position;
	register const int		intlen = sizeof(long long int) * CHAR_BIT;

	errno ^= errno;
	if (!i)
		return (0);
	mask = 0x1;
	position = 1;
	while (!((unsigned long long int)(i) & mask) && position <= intlen)
	{
		mask <<= 1;
		position++;
	}
	return (position);
}
