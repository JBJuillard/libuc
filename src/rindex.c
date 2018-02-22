/*
** rindex function for Undefined-C library
**
** Created: 01/24/2018 by Juillard Jean-Baptiste
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

#include <libuc/errno.h>
#include <stdlib.h>

char	*rindex(const char *s, int c)
{
	register unsigned char	*ptr;

	if (!(ptr = (unsigned char *)(s))
		|| c < 0x00 || c > 0xFF)
	{
		errno = EINVAL;
		return (NULL);
	}
	errno ^= errno;
	while (*ptr)
		ptr++;
	while (ptr >= (unsigned char *)(s))
	{
		if (*ptr == (unsigned char)(c))
			return ((char *)(ptr));
		ptr--;
	}
	return (NULL);
}
