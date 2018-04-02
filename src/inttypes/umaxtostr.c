/*
** umaxtostr.c
**
** umaxtostr function of Undefined-C library
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
#include <libuc/stdlib.h>
#include <libuc/stdint.h>
#include <libuc/limits.h>

char	*umaxtostr(uintmax_t n, int base, int upcasse)
{
	static unsigned char	t[((sizeof(uintmax_t) * CHAR_BIT) + 1)];
	register size_t			i;
	register uintmax_t		c;
	register uintmax_t		b;

	if (n > UINTMAX_MAX || base < 2 || base > 36)
	{
		errno = EINVAL;
		return ((char *)(NULL));
	}
	errno = 0;
	b = (uintmax_t)(base);
	i = (sizeof(uintmax_t) * CHAR_BIT);
	t[i] = '\0';
	if (!n)
		t[--i] = '0';
	else
	{
		while (n)
		{
			c = n % b;
			n /= b;
			if (c > UINTMAX_C(9))
			{
				if (upcasse)
					c += (uintmax_t)('A');
				else
					c += (uintmax_t)('a');
			}
			else
				c += (uintmax_t)('0');
			t[--i] = (unsigned char)(c);
		}
	}
	return ((char *)(t + i));
}
