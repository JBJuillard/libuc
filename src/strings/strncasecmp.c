/*
** strncasecmp.c
**
** strncasecmp function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/01/22 by Juillard Jean-Baptiste
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

#include <libuc/stddef.h>
#include <libuc/stdint.h>
#include <libuc/errno.h>

int	strncasecmp(const char *s1, const char *s2, size_t n)
{
	register unsigned char	*p1;
	register unsigned char	*p2;
	register unsigned char	c1;
	register unsigned char	c2;

	if (!(p1 = (unsigned char *)(s1))
		|| !(p2 = (unsigned char *)(s2))
		|| !n || n > SIZE_MAX)
	{
		errno = EINVAL;
		return (0);
	}
	errno ^= errno;
	while ((*p1 || *p2) && n)
	{
		c1 = (*p1 >= 'a' && *p1 <= 'z') ? (*p1 - 0x20) : *p1;
		c2 = (*p2 >= 'a' && *p2 <= 'z') ? (*p2 - 0x20) : *p2;
		if (c1 != c2)
			return ((int)(c1 - c2));
		p1++;
		p2++;
		n--;
	}
	return (0);
}
