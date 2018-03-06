/*
** bsearch function for Undefined-C library
**
** Created: 02/25/2018 by Juillard Jean-Baptiste
** Updated: 02/25/2018 by Juillard Jean-Baptiste
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

void	*bsearch(const void *key, const void *base, size_t nmemb,
			size_t size, int (*compar)(const void *, const void *))
{
	register size_t		i;
	register const void	*k;
	register const void	*b;
	register size_t		m;
	register size_t		s;
	register int		(*f)(const void *, const void *);

	if (!(k = key) || !(b = base)
		|| !(m = nmemb) || m > SIZE_MAX
		|| !(s = size) || s  > SIZE_MAX
		|| !(f = compar))
	{
		errno = EINVAL;
		return (NULL);
	}
	i ^= i;
	errno ^= errno;
	while (i < m)
	{
		if (!(*f)(k, b))
			return (b);
		b += s;
		if (i == SIZE_MAX)
		{
			errno = EOVERFLOW;
			return (NULL);
		}
		i++;
	}
	return (NULL);
}
