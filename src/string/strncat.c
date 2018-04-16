/*
** strncat.c
**
** strncat function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/01/21 by Juillard Jean-Baptiste
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

#include <libuc/stddef.h>
#include <libuc/stdint.h>
#include <libuc/errno.h>
#include <libuc/stdlib.h>

char	*strncat(char *s1, const char *s2, size_t n)
{
	register char	*p1;
	register char	*p2;

	if (!(p1 = s1)
		|| !(p2 = (char *)(s2))
		|| !n || n > SIZE_MAX)
	{
		errno = EINVAL;
		return ((char *)(NULL));
	}
	errno = 0;
	while (*p1)
		p1++;
	while (n && *p2)
	{
		*(p1++) = *(p2++);
		n--;
	}
	*p1 = '\0';
	return (s1);
}
