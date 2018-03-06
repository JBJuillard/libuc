/*
** strtoll function for Undefined-C library
**
** Created: 02/24/2018 by Juillard Jean-Baptiste
** Updated: 02/25/2018 by Juillard Jean-Baptiste
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

#define		_XDIGIT_0		(48ULL)
#define		_XDIGIT_9		(57ULL)
#define		_XDIGIT_A		(65ULL)
#define		_XDIGIT_Z		(90ULL)
#define		_XDIGIT_a		(97ULL)
#define		_XDIGIT_z		(122ULL)

#define		_ULL_LLONG_MAX		((unsigned long long int)(LLONG_MAX))
#define		_ULL_LLONG_MIN		((unsigned long long int)(LLONG_MAX) + 1ULL)

long long int	strtoll(const char *nptr, char **endptr, int base)
{
	register const char		*p;
	register unsigned long long int	n;
	register unsigned long long int	b;
	register char			neg;
	register unsigned long long int	dmax;
	register unsigned long long int	c;
	register unsigned long long int	cmax;

	if (!nptr || (base && base < 2) || base > 36)
	{
		errno = EINVAL;
		return (0);
	}
	errno ^= errno;
	p = nptr;
	n ^= n;
	b = ((base) ? (unsigned long long int)(base) : 10ULL);
	cmax ^= cmax;
	if (b <= 10ULL)
		dmax = b - 1ULL + _XDIGIT_0;
	else if (b > 10ULL)
	{
		dmax = _XDIGIT_9;
		cmax = b - 11ULL + _XDIGIT_A;
	}
	while (*p == '\f' || *p == '\n' || *p == '\r' || *p == '\t' || *p == '\v')
		p++;
	neg ^= neg;
	if (*p == '-')
		neg = *(p++);
	else if (*p == '+')
		p++;
	while ((c = (unsigned long long int)(*p))
		&& ((c >= _XDIGIT_a && c <= _XDIGIT_z) ? (c -= 32ULL) : (c))
		&& ((b <= 10ULL && c >= _XDIGIT_0 && c <= dmax)
			|| (b > 10ULL
				&& ((c >= _XDIGIT_0 && c <= _XDIGIT_9)
					|| (c >= _XDIGIT_A && c <= cmax)))))
	{
		if (c >= _XDIGIT_A && c <= cmax)
			c -= _XDIGIT_A;
		else
			c -= _XDIGIT_0;
		if (!neg
			&& (n > (_ULL_LLONG_MAX / b)
				|| (n == (_ULL_LLONG_MAX / b)
					&& c > (_ULL_LLONG_MAX % b))))
		{
			errno = ERANGE;
			return (LLONG_MAX);
		}
		else if (neg
			&& (n > (_ULL_LLONG_MIN / b)
				|| (n == (_ULL_LLONG_MIN / b)
					&& c > (_ULL_LLONG_MIN % b))))
		{
			errno = ERANGE;
			return (LLONG_MIN);
		}
		n = (n * b) + c;
		p++;
	}
	if (endptr)
		*endptr = (char *)(p);
	if (neg)
		return ((long long int)(-n));
	return ((long long int)(n));
}
