/*
** strrchr function for Undefined-C library
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

#include <libuc/errno.h>
#include <stdlib.h>

char	*strrchr(const char *s, int c)
{
	register unsigned char	*p;

	if (!(p = (unsigned char *)(s))
		|| c < 0x00 || c > 0xFF)
	{
		errno = EINVAL;
		return ((char *)(NULL));
	}
	errno ^= errno;
	while (*p)
		p++;
	while (p >= (unsigned char *)(s))
	{
		if (*p == (unsigned char)(c))
			return ((char *)(p));
		p--;
	}
	return ((char *)(NULL));
}
