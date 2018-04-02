/*
** strtoimax.c
**
** strtoi function of Undefined-C library
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
#include <libuc/limits.h>
#include <libuc/stdint.h>

#define		_XDIGIT_0		(UINTMAX_C(48))
#define		_XDIGIT_9		(UINTMAX_C(57))
#define		_XDIGIT_A		(UINTMAX_C(65))
#define		_XDIGIT_Z		(UINTMAX_C(90))
#define		_XDIGIT_a		(UINTMAX_C(97))
#define		_XDIGIT_z		(UINTMAX_C(122))

#define		_UL_IMAX_MAX	((uintmax_t)(INTMAX_MAX))
#define		_UL_IMAX_MIN	((uintmax_t)(INTMAX_MAX) + UINTMAX_C(1))

intmax_t	strtoimax(const char * restrict nptr, char ** restrict endptr, int base)
{
	register const char		*p;
	register uintmax_t		n;
	register uintmax_t		b;
	register char			neg;
	register uintmax_t		dmax;
	register uintmax_t		c;
	register uintmax_t		cmax;

	if (!nptr || (base && base < 2) || base > 36)
	{
		errno = EINVAL;
		return (0);
	}
	errno ^= errno;
	p = nptr;
	n ^= n;
	b = ((base) ? (uintmax_t)(base) : UINTMAX_C(10));
	cmax ^= cmax;
	if (b <= UINTMAX_C(10))
		dmax = b - UINTMAX_C(1) + _XDIGIT_0;
	else if (b > UINTMAX_C(10))
	{
		dmax = _XDIGIT_9;
		cmax = b - UINTMAX_C(11) + _XDIGIT_A;
	}
	while (*p == '\f' || *p == '\n' || *p == '\r' || *p == '\t' || *p == '\v')
		p++;
	neg ^= neg;
	if (*p == '-')
		neg = *(p++);
	else if (*p == '+')
		p++;
	while ((c = (uintmax_t)(*p))
			&& ((c >= _XDIGIT_a && c <= _XDIGIT_z) ? (c -= UINTMAX_C(32)) : (c))
			&& ((b <= UINTMAX_C(10) && c >= _XDIGIT_0 && c <= dmax)
				|| (b > UINTMAX_C(10)
					&& ((c >= _XDIGIT_0 && c <= _XDIGIT_9)
						|| (c >= _XDIGIT_A && c <= cmax)))))
	{
		if (c >= _XDIGIT_A && c <= cmax)
			c -= _XDIGIT_A;
		else
			c -= _XDIGIT_0;
		if (!neg
			&& (n > (_UL_IMAX_MAX / b)
				|| (n == (_UL_IMAX_MAX / b)
					&& c > (_UL_IMAX_MAX % b))))
		{
			errno = ERANGE;
			return (INTMAX_MAX);
		}
		else if (neg
			&& (n > (_UL_IMAX_MIN / b)
				|| (n == (_UL_IMAX_MIN / b)
					&& c > (_UL_IMAX_MIN % b))))
		{
			errno = ERANGE;
			return (INTMAX_MIN);
		}
		n = (n * b) + c;
		p++;
	}
	if (endptr)
		*endptr = (char *)(p);
	if (neg)
		return ((intmax_t)(-n));
	return ((intmax_t)(n));
}
