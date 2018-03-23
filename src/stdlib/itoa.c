/*
** itoa.c
**
** itoa function of Undefined-C library
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

char	*itoa(int n)
{
	register unsigned int	nb;
	auto unsigned char		t[16];
	register size_t			i;
	register unsigned int	c;
	register int			neg;
	register unsigned char	*s;

	if (n < INT_MIN || n > INT_MAX)
	{
		errno = EINVAL;
		return ((char *)(NULL));
	}
	errno = 0;
	neg ^= neg;
	if (n < 0)
	{
		nb = (unsigned int)(-n);
		neg++;
	}
	else
		nb = (unsigned int)(n);
	t[15] = '\0';
	i = 15;
	while (nb)
	{
		c = nb % 10U;
		nb /= 10U;
		c += (unsigned int)('0');
		t[--i] = (unsigned char)(c);
	}
	if (neg)
		t[--i] = '-';
	if ((s = (unsigned char *)malloc(16 - i)) == (unsigned char *)(NULL))
		return ((char *)(NULL));
	c ^= c;
	while (c < 16)
		*(s + c++) = t[i++];
	return ((char *)(s));
}