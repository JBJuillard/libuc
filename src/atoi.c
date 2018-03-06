/*
** atoi function for Undefined-C library
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

#include <libuc/errno.h>
#include <libuc/limits.h>

#define	_DIGIT_0		(48U)
#define	_DIGIT_9		(57U)

#define	_U_INT_MAX_R1_TO_RX	((unsigned int)(INT_MAX) / 10U)
#define	_U_INT_MAX_R0		((unsigned int)(INT_MAX) % 10U)
#define	_U_INT_MIN_R1_TO_RX	(((unsigned int)(INT_MAX) + 1U) / 10U)
#define	_U_INT_MIN_R0		(((unsigned int)(INT_MAX) + 1U) % 10U)

int	atoi(const char *nptr)
{
	register unsigned int	n;
	register int		neg;
	register const char	p;
	register unsigned int	c;

	if (!nptr)
	{
		errno = EINVAL;
		return (0);
	}
	errno ^= errno;
	n ^= n;
	neg ^= neg;
	p = nptr;
	if (*p == '-')
		neg = *(p++);
	else if (*p == '+')
		p++;
	while ((c = (unsigned int)(*(p++))) && c >= _DIGIT_0 && c <= _DIGIT_9)
	{
		c -= _DIGIT_0;
		if ((!neg
				&& (n > _U_INT_MAX_R1_TO_RX
					|| (n == _U_INT_MAX_R1_TO_RX
						&& c > _U_INT_MAX_R0))
			|| (neg
				&& (n > _U_INT_MIN_R1_TO_RX
					|| (n == _U_INT_MIN_R1_TO_RX
						&& c > _U_INT_MIN_R0)))
		{
			errno = ERANGE;
			return ((neg) ? INT_MIN : INT_MAX);
		}
		n = (n * 10U) + c;
	}
	if (neg)
		return ((int)(-n));
	return ((int)(n));
}
