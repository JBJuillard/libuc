/*
** strtok_s function for Undefined-C library
**
** Created: 01/25/2018 by Juillard Jean-Baptiste
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

#define __STDC_WANT_LIB_EXT1__		1

#include <libuc/stddef.h>
#include <libuc/stdint.h>
#include <libuc/errno.h>
#include <stdlib.h>

char	*strtok_s(char *s1, rsize_t s1max, const char *s2, char **ptr)
{
	register size_t	offset1;
	register size_t	offset2;
	register int	nostr;

	if (!s1max || s1max > RSIZE_MAX || !s2 || !ptr || (!s1 && !*ptr))
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
	while (offset1 < (size_t)(s1max) && *(s1 + offset1))
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
					s1max--;
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