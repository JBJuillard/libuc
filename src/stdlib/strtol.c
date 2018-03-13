/*
** strtol.c
**
** strtol function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/02/25 by Juillard Jean-Baptiste
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

#include	<libuc/errno.h>
#include	<libuc/limits.h>

#define		_XDIGIT_0		(48UL)
#define		_XDIGIT_9		(57UL)
#define		_XDIGIT_A		(65UL)
#define		_XDIGIT_Z		(90UL)
#define		_XDIGIT_a		(97UL)
#define		_XDIGIT_z		(122UL)

#define		_UL_LONG_MAX	((unsigned long int)(LONG_MAX))
#define		_UL_LONG_MIN	((unsigned long int)(LONG_MAX) + 1UL)

long int	strtol(const char *nptr, char **endptr, int base)
{
	register const char			*p;
	register unsigned long int	n;
	register unsigned long int	b;
	register char				neg;
	register unsigned long int	dmax;
	register unsigned long int	c;
	register unsigned long int	cmax;

	if (!nptr || (base && base < 2) || base > 36)
	{
		errno = EINVAL;
		return (0);
	}
	errno ^= errno;
	p = nptr;
	n ^= n;
	b = ((base) ? (unsigned long int)(base) : 10UL);
	cmax ^= cmax;
	if (b <= 10UL)
		dmax = b - 1UL + _XDIGIT_0;
	else if (b > 10UL)
	{
		dmax = _XDIGIT_9;
		cmax = b - 11UL + _XDIGIT_A;
	}
	while (*p == '\f' || *p == '\n' || *p == '\r' || *p == '\t' || *p == '\v')
		p++;
	neg ^= neg;
	if (*p == '-')
		neg = *(p++);
	else if (*p == '+')
		p++;
	while ((c = (unsigned long int)(*p))
		&& ((c >= _XDIGIT_a && c <= _XDIGIT_z) ? (c -= 32UL) : (c))
		&& ((b <= 10UL && c >= _XDIGIT_0 && c <= dmax)
			|| (b > 10UL
				&& ((c >= _XDIGIT_0 && c <= _XDIGIT_9)
					|| (c >= _XDIGIT_A && c <= cmax)))))
	{
		if (c >= _XDIGIT_A && c <= cmax)
			c -= _XDIGIT_A;
		else
			c -= _XDIGIT_0;
		if (!neg
			&& (n > (_UL_LONG_MAX / b)
				|| (n == (_UL_LONG_MAX / b)
					&& c > (_UL_LONG_MAX % b))))
		{
			errno = ERANGE;
			return (LONG_MAX);
		}
		else if (neg
			&& (n > (_UL_LONG_MIN / b)
				|| (n == (_UL_LONG_MIN / b)
					&& c > (_UL_LONG_MIN % b))))
		{
			errno = ERANGE;
			return (LONG_MIN);
		}
		n = (n * b) + c;
		p++;
	}
	if (endptr)
		*endptr = (char *)(p);
	if (neg)
		return ((long int)(-n));
	return ((long int)(n));
}
