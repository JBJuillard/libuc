/*
** strcasestr function for Undefined-C library
**
** Created: 01/23/2018 by Juillard Jean-Baptiste
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

#include <libuc/stddef.h>
#include <libuc/stdint.h>
#include <libuc/errno.h>
#include <stdlib.h>

char	*strcasestr(const char *s1, const char *s2)
{
	register size_t	offset;
	register char	c1;
	register char	c2;

	if (!s1 || !s2)
	{
		errno = EINVAL;
		return ((char *)(NULL));
	}
	errno ^= errno;
	if (!*s2)
		return ((char *)(s1));
	while (*s1)
	{
		offset ^= offset;
		while (*(s2 + offset))
		{
			if (*(s1 + offset) >= 'a' && *(s1 + offset) <= 'z')
				c1 = *(s1 + offset) - 32;
			else
				c1 = *(s1 + offset);
			if (*(s2 + offset) >= 'a' && *(s2 + offset) <= 'z')
				c2 = *(s2 + offset) - 32;
			else
				c2 = *(s2 + offset);
			if (c1 != c2)
				break ;
			offset++;
		}
		if (!*(s2 + offset))
			return ((char *)(s1));
		s1++;
	}
	return ((char *)(NULL));
}
