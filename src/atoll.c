/*
** atoll function for Undefined-C library
**
** Created: 02/25/2018 by Juillard Jean-Baptiste
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

#include <libuc/errno.h>
#include <libuc/limits.h>

#define	_DIGIT_0		(48ULL)
#define	_DIGIT_9		(57ULL)

#define	_U_LLONG_MAX_R1_TO_RX	((unsigned long long int)(LLONG_MAX) / 10ULL)
#define	_U_LLONG_MAX_R0		((unsigned long long int)(LLONG_MAX) % 10ULL)
#define	_U_LLONG_MIN_R1_TO_RX	(((unsigned long long int)(LLONG_MAX) + 1ULL) / 10ULL)
#define	_U_LLONG_MIN_R0		(((unsigned long int)(LLONG_MAX) + 1ULL) % 10ULL)

long long int	atoll(const char *nptr)
{
	register unsigned long long int	n;
	register long long int		neg;
	register const char		p;
	register unsigned long long int	c;

	if (!nptr)
	{
		errno = EINVAL;
		return (0);
	}
	errno ^= errno;
	n ^= n;
	p = nptr;
	while (*p == '\f' || *p == '\n' || *p == '\r' || *p == '\t' || *p == '\v')
		p++;
	neg ^= neg;
	if (*p == '-')
		neg = *(p++);
	else if (*p == '+')
		p++;
	while ((c = (unsigned long long int)(*(p++))) && c >= _DIGIT_0 && c <= _DIGIT_9)
	{
		c -= _DIGIT_0;
		if ((!neg
				&& (n > _U_LLONG_MAX_R1_TO_RX
					|| (n == _U_LLONG_MAX_R1_TO_RX
						&& c > _U_LLONG_MAX_R0))
			|| (neg
				&& (n > _U_LLONG_MIN_R1_TO_RX
					|| (n == _U_LLONG_MIN_R1_TO_RX
						&& c > _U_LLONG_MIN_R0)))
		{
			errno = ERANGE;
			return ((neg) ? LLONG_MIN : LLONG_MAX);
		}
		n = (n * 10ULL) + c;
	}
	if (neg)
		return ((long long int)(-n));
	return ((long long int)(n));
}
