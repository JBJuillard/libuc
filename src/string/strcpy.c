/*
** strcpy.c
**
** strcpy function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/01/20 by Juillard Jean-Baptiste
** Updated: 2018/04/15 by Juillard Jean-Baptiste
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
#include <libuc/stdlib.h>

char	*strcpy(char * restrict s1, const char * restrict s2)
{
	register unsigned char			*p1;
	register const unsigned char	*p2;

	if (!(p1 = (unsigned char *)(s1))
		|| !(p2 = (const unsigned char *)(s2)))
	{
		errno = EINVAL;
		return ((char *)(NULL));
	}
	errno = 0;
	while (*p2)
		*(p1++) = *(p2++);
	*p1 = '\0';
	return (s1);
}
