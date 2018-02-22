/*
** ffsl function for Undefined-C library
**
** Created: 01/24/2018 by Juillard Jean-Baptiste
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
#include <limits.h>

int	ffsl(long int i)
{
	register unsigned long int	mask;
	register int			position;
	register const int		intlen = sizeof(long int) * CHAR_BIT;

	errno ^= errno;
	if (!i)
		return (0);
	mask = 0x1;
	position = 1;
	while (!((unsigned long int)(i) & mask) && position <= intlen)
	{
		mask <<= 1;
		position++;
	}
	return (position);
}
