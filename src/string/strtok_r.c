/*
** strtok_r.c
**
** strtok_r function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/01/25 by Juillard Jean-Baptiste
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
#include <stdlib.h>

char	*strtok_r(char *s1, const char *s2, char **ptr)
{
	register size_t	offset1;
	register size_t	offset2;
	register int	nostr;

	if (!s2 || !ptr || (!s1 && !*ptr))
	{
		errno = EINVAL;
		return ((char *)(NULL));
	}
	errno ^= errno;
	if (!s1 && *ptr)
		s1 = *ptr;
	if (!*s1)
	{
		*ptr = (char *)(NULL);
		return ((char *)(NULL));
	}
	offset1 ^= offset1;
	while (*(s1 + offset1))
	{
		offset2 ^= offset2;
		if (!offset1)
			nostr ^= nostr;
		while (*(s2 + offset2))
		{
			if (*(s2 + offset2) == *(s1 + offset1))
			{
				if (!offset1)
				{
					nostr = 1;
					s1++;
					break ;
				}
				*ptr = s1 + offset1 + 1;
				*(s1 + offset1) = '\0';
				return (s1);
			}
			offset2++;
		}
		if (nostr)
			continue ;
		offset1++;
	}
	*ptr = s1 + offset1;
	return (s1);
}
