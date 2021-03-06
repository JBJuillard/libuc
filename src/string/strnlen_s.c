/*
** strnlen_s.c
**
** strnlen_s function of Undefined-C library
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

# define __STDC_WANT_LIB_EXT1__		1

#include <libuc/stddef.h>
#include <libuc/stdint.h>
#include <libuc/errno.h>

size_t	strnlen_s(const char *s1, size_t sizemax)
{
	register size_t		size;
	register size_t		max;
	register const char	*str;;

	if (!s1 || !sizemax || sizemax > SIZE_MAX)
	{
		errno = EINVAL;
		return ((size_t)(0));
	}
	errno = 0;
	size ^= size;
	max = sizemax;
	str = s1;
	while (size < max && *(str++))
		size++;
	return (size);
}
