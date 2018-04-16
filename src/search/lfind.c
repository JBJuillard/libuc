/*
** lfind.c
**
** lfind function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/04/06 by Juillard Jean-Baptiste
** Updated: 2018/04/07 by Juillard Jean-Baptiste
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
#include <libuc/errno.h>

void	*lfind(const void *key, const void *base, size_t *nmemb, size_t size,
				int (*compar)(const void *, const void *))
{
	register const void	*k;
	register const void	*b;
	register size_t		n;
	register size_t		s;
	register int		(*f)(const void *, const void *);
	register size_t		i;

	if (!key || !base || !nmemb || !size || !compar)
	{
		errno = EINVAL;
		return (NULL);
	}
	errno = 0;
	k = key;
	b = base;
	n = *nmemb;
	s = size;
	f = compar;
	i ^= i;
	while (i < n)
	{
		if (!((*f)(key, (b + (i * s)))))
			return ((b + (i * s)));
		i++;
	}
	return (NULL);
}
