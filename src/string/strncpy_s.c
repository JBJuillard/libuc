/*
** strncpy_s.c
**
** strncpy_s function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/01/21 by Juillard Jean-Baptiste
** Updated: 2018/03/21 by Juillard Jean-Baptiste
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
#include <libuc/string.h>

errno_t	strncpy_s(char * restrict s1, rsize_t s1max,
					const char * restrict s2, rsize_t n)
{
	register unsigned char			*p1;	/* Fast pointer on s1 */
	register const unsigned char	*p2;	/* Fast pointer on s2 */
	register rsize_t				c;		/* Fast counter */

	if (!s1 || !s1max || s1max > RSIZE_MAX || !s2
		|| s1max == strnlen_s(s2, s1max)
		|| !n || n >= s1max)
	{
		if (s1 && s1max && s1max <= RSIZE_MAX)
			*s1 = '\0';
		errno = EINVAL;
		return ((errno_t)(EINVAL));
	}
	errno = 0;
	p1 = (unsigned char *)(s1);
	p2 = (const unsigned char *)(s2);
	while (*p2 && c)
	{
		*(p1++) = *((unsigned char *)(p2++));
		c--;
	}
	if (*p2)
		*((unsigned char *)(s1 + n)) = '\0';
	return ((errno_t)(0));
}
