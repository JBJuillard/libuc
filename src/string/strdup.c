/*
** strdup.c
**
** strdup function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/01/22 by Juillard Jean-Baptiste
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
#include <stdlib.h>

char	*strdup(const char *s)
{
	register char	*t;
	register char	*p;
	register size_t	l;

	if (!(t = (char *)(s)))
	{
		errno = EINVAL;
		return ((char *)(NULL));
	}
	errno = 0;
	while (*t)
		t++;
	l = (size_t)(t - s);
	if ((p = (char *)malloc(l + 1)) == (char *)(NULL))
		return ((char *)(NULL));
	*(p + l) = '\0';
	t = p;
	while (*s)
		*(t++) = *(s++);
	return (p);
}
