/*
** atou.c
**
** atou function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/26 by Juillard Jean-Baptiste
** Updated: 2018/03/26 by Juillard Jean-Baptiste
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

#define	_DIGIT_0				(48U)
#define	_DIGIT_9				(57U)

#define	_U_UINT_MAX_R1_TO_RX	(UINT_MAX / 10U)
#define	_U_UINT_MAX_R0			(UINT_MAX % 10U)

unsigned int	atou(const char *nptr)
{
	register unsigned int	n;
	register char			*p;
	register unsigned int	c;

	if (!nptr)
	{
		errno = EINVAL;
		return (0);
	}
	errno = 0;
	n ^= n;
	p = (char *)(nptr);
	if (*p == '+')
		p++;
	while ((c = (unsigned int)(*((char *)(p++))))
			&& c >= (unsigned int)('0')
			&& c <= (unsigned int)('9'))
	{
		c -= _DIGIT_0;
		if (((n > _U_UINT_MAX_R1_TO_RX
			|| (n == _U_UINT_MAX_R1_TO_RX
				&& c > _U_UINT_MAX_R0))))
		{
			errno = ERANGE;
			return (UINT_MAX);
		}
		n = (n * 10U) + c;
	}
	return (n);
}
