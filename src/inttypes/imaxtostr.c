/*
** imaxtostr.c
**
** imaxtostr function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/30 by Juillard Jean-Baptiste
** Updated: 2018/03/30 by Juillard Jean-Baptiste
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

char	*imaxtostr(intmax_t n, int base, int upcasse)
{
	static unsigned char	t[128];
	register uintmax_t		nb;
	register uintmax_t		b;
	register size_t			i;
	register uintmax_t		c;
	register int			neg;

	if (n < INTMAX_MIN || n > INTMAX_MAX || base < 2 || base > 36)
	{
		errno = EINVAL;
		return ((char *)(NULL));
	}
	errno = 0;
	neg ^= neg;
	b = (uintmax_t)(base);
	if (n < INTMAX_C(0))
	{
		nb = (uintmax_t)(-n);
		neg++;
	}
	else
		nb = (uintmax_t)(n);
	t[127] = '\0';
	i = 127;
	if (!nb)
		t[--i] = '0';
	else
	{
		while (nb)
		{
			c = nb % b;
			nb /= b;
			if (c > UINTMAX_C(9))
				c += (upcasse ? (uintmax_t)('A') : (uintmax_t)('a'));
			else
				c += (uintmax_t)('0');
			t[--i] = (unsigned char)(c);
		}
		if (neg)
			t[--i] = '-';
	}
	return ((char *)(t + i));
}
