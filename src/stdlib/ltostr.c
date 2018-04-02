/*
** ltostr.c
**
** ltostr function of Undefined-C library
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

char	*ltostr(long int n, int base, int upcasse)
{
	static unsigned char		t[((sizeof(long int) * CHAR_BIT) + 2)];
	register unsigned long int	nb;
	register size_t				i;
	register unsigned long int	c;
	register int				neg;

	if (n < LONG_MIN || n > LONG_MAX || base < 2 || base > 36)
	{
		errno = EINVAL;
		return ((char *)(NULL));
	}
	errno = 0;
	neg ^= neg;
	if (n < 0)
	{
		nb = (unsigned long int)(-n);
		neg++;
	}
	else
		nb = (unsigned long int)(n);
	i = ((sizeof(long int) * CHAR_BIT) + 1);
	t[i] = '\0';
	if (!nb)
		t[--i] = '0';
	else
	{
		while (nb)
		{
			c = nb % (unsigned long int)(base);
			nb /= (unsigned long int)(base);
			if (c > 9UL)
			{
				if (upcasse)
					c += (unsigned long int)('A');
				else
					c += (unsigned long int)('a');
			}
			else
				c += (unsigned long int)('0');
			t[--i] = (unsigned char)(c);
		}
		if (neg)
			t[--i] = '-';
	}
	return ((char *)(t + i));
}
