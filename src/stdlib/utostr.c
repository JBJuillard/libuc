/*
** utostr.c
**
** utostr function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/14 by Juillard Jean-Baptiste
** Updated: 2018/03/31 by Juillard Jean-Baptiste
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
#include <libuc/limits.h>
#include <libuc/stdlib.h>

char	*utostr(unsigned int n, int base, int upcasse)
{
	static unsigned char	t[((sizeof(unsigned int) * CHAR_BIT) + 1)];
	register size_t			i;
	register unsigned int	c;
	register unsigned int	b;

	if (n > UINT_MAX || base < 2 || base > 36)
	{
		errno = EINVAL;
		return ((char *)(NULL));
	}
	errno = 0;
	b = (unsigned int)(base);
	i = (sizeof(unsigned int) * CHAR_BIT);
	t[i] = '\0';
	if (!n)
		t[--i] = '0';
	else
	{
		while (n)
		{
			c = n % b;
			n /= b;
			if (c > 9U)
			{
				if (upcasse)
					c += (unsigned int)('A');
				else
					c += (unsigned int)('a');
			}
			else
				c += (unsigned int)('0');
			t[--i] = (unsigned char)(c);
		}
	}
	return ((char *)(t + i));
}
