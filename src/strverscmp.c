/*
** strverscmp function for Undefined-C library
**
** Created: 01/22/2018 by Juillard Jean-Baptiste
** Updated: 01/25/2018 by Juillard Jean-Baptiste
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

#include <limits.h>
#include <libuc/errno.h>

int	strverscmp(const char *s1, const char *s2)
{
	register const unsigned char	*p1;
	register const unsigned char	*p2;
	register int			s1zero;
	register int			s2zero;
	register unsigned int		n1;
	register unsigned int		n2;

	if (!s1 || !s2)
	{
		errno = EINVAL;
		return (0);
	}
	errno ^= errno;
	p1 = (const unsigned char *)(s1);
	p2 = (const unsigned char *)(s2);
	s1zero ^= s1zero;
	s2zero ^= s2zero;
	n1 ^= n1;
	n2 ^= n2;
	while ((*p1 || *p2)
		&& (*p1 < '0' || *p1 > '9')
		&& (*p2 < '0' || *p2 > '9'))
	{
		if (*p1 != *p2)
			return ((int)(*p1) - (int)(*p2));
		p1++;
		p2++;
	}
	if (*p1 == '0')
		s1zero = 1;
	if (*p2 == '0')
		s2zero = 1;
	while ((*p1 || *p2)
		&& ((*p1 >= '0' && *p1 <= '9')
			|| (*p2 >= '0' && *p2 <= '9')))
	{
		if (s1zero | s2zero)
		{
			if (*p1 != *p2)
				return ((int)(*p1) - (int)(*p2));
		}
		else
		{
			if (*p1 >= '0' && *p1 <= '9')
			{
				if ((UINT_MAX / 10) < n1
					|| ((UINT_MAX / 10) == n1
						&& (UINT_MAX % 10) < (unsigned int)(*p1 - '0')))
				{
					errno = EOVERFLOW;
					return (0);
				}
				n1 = (n1 * 10) + (*p1 - '0');
			}
			if (*p2 >= '0' && *p2 <= '9')
			{
				if ((UINT_MAX / 10) <= n2
					|| ((UINT_MAX / 10) == n2
						&& (UINT_MAX % 10) < (unsigned int)(*p2 - '0')))
				{
					errno = EOVERFLOW;
					return (0);
				}
				n2= (n2 * 10) + (*p2 - '0');
			}
		}
		if (*p1 >= '0' && *p1 <= '9')
			p1++;
		if (*p2 >= '0' && *p2 <= '9')
			p2++;
	}
	if (n1 || n2)
		return ((int)(n1) - (int)(n2));
	return (0);
}
