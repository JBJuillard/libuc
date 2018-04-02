/*
** strtoi.c
**
** strtoi function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/02/25 by Juillard Jean-Baptiste
** Updated: 2018/03/27 by Juillard Jean-Baptiste
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

#define		_XDIGIT_0		(48U)
#define		_XDIGIT_9		(57U)
#define		_XDIGIT_A		(65U)
#define		_XDIGIT_Z		(90U)
#define		_XDIGIT_a		(97U)
#define		_XDIGIT_z		(122U)

#define		_UL_INT_MAX		((unsigned int)(INT_MAX))
#define		_UL_INT_MIN		((unsigned int)(INT_MAX) + 1UL)

int	strtoi(const char *nptr, char **endptr, int base)
{
	register const char		*p;
	register unsigned int	n;
	register unsigned int	b;
	register char			neg;
	register unsigned int	dmax;
	register unsigned int	c;
	register unsigned int	cmax;

	if (!nptr || (base && base < 2) || base > 36)
	{
		errno = EINVAL;
		return (0);
	}
	errno ^= errno;
	p = nptr;
	n ^= n;
	b = ((base) ? (unsigned int)(base) : 10UL);
	cmax ^= cmax;
	if (b <= 10U)
		dmax = b - 1U + _XDIGIT_0;
	else if (b > 10U)
	{
		dmax = _XDIGIT_9;
		cmax = b - 11U + _XDIGIT_A;
	}
	while (*p == '\f' || *p == '\n' || *p == '\r' || *p == '\t' || *p == '\v')
		p++;
	neg ^= neg;
	if (*p == '-')
		neg = *(p++);
	else if (*p == '+')
		p++;
	while ((c = (unsigned int)(*p))
		&& ((c >= _XDIGIT_a && c <= _XDIGIT_z) ? (c -= 32U) : (c))
		&& ((b <= 10U && c >= _XDIGIT_0 && c <= dmax)
			|| (b > 10U
				&& ((c >= _XDIGIT_0 && c <= _XDIGIT_9)
					|| (c >= _XDIGIT_A && c <= cmax)))))
	{
		if (c >= _XDIGIT_A && c <= cmax)
			c -= _XDIGIT_A;
		else
			c -= _XDIGIT_0;
		if (!neg
			&& (n > (_UL_INT_MAX / b)
				|| (n == (_UL_INT_MAX / b)
					&& c > (_UL_INT_MAX % b))))
		{
			errno = ERANGE;
			return (INT_MAX);
		}
		else if (neg
			&& (n > (_UL_INT_MIN / b)
				|| (n == (_UL_INT_MIN / b)
					&& c > (_UL_INT_MIN % b))))
		{
			errno = ERANGE;
			return (INT_MIN);
		}
		n = (n * b) + c;
		p++;
	}
	if (endptr)
		*endptr = (char *)(p);
	if (neg)
		return ((int)(-n));
	return ((int)(n));
}
