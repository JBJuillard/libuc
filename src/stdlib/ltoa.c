/*
** ltoa.c
**
** ltoa function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/14 by Juillard Jean-Baptiste
** Updated: 2018/03/14 by Juillard Jean-Baptiste
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

#include <libuc/limits.h>
#include <libuc/errno.h>
#include <libuc/stdlib.h>

char	*ltoa(long int n)
{
	register unsigned long int	nb;
	auto unsigned char			t[32];
	register size_t				i;
	register unsigned long int	c;
	register int				neg;
	register unsigned char		*s;

	if (n < LONG_MIN || n > LONG_MAX)
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
	t[31] = '\0';
	i = 31;
	while (nb)
	{
		c = nb % 10UL;
		nb /= 10UL;
		c += (unsigned long int)('0');
		t[--i] = (unsigned char)(c);
	}
	if (neg)
		t[--i] = '-';
	if ((s = (unsigned char *)malloc(32 - i)) == (unsigned char *)(NULL))
		return ((char *)(NULL));
	c ^= c;
	while (c < 32)
		*(s + c++) = t[i++];
	return ((char *)(s));
}
