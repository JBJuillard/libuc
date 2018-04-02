/*
** strtoumax.c
**
** strtou function of Undefined-C library
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

uintmax_t	strtoumax(const char * restrict nptr, char ** restrict endptr, int base)
{
	register const char		*p;
	register uintmax_t		n;
	register uintmax_t		b;
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
	if (*p == '+')
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
		if (n > (UINTMAX_MAX / b)
			|| (n == (UINTMAX_MAX / b)
				&& c > (UINTMAX_MAX % b)))
		{
			errno = ERANGE;
			return (UINTMAX_MAX);
		}
		n = (n * b) + c;
		p++;
	}
	if (endptr)
		*endptr = (char *)(p);
	return (n);
}
