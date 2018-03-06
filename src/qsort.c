/*
** qsort function for Undefined-C library
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
#include <libuc/string.h>

void	qsort(const void *base, size_t nmemb, size_t size,
			int (*compar)(const void *, const void *))
{
	register size_t		i;
	register const void	*b;
	register size_t		m;
	register size_t		s;
	register int		(*f)(const void *, const void *);
	register void		*t;
	register int		c;

	if (!(b = base)
		|| !(m = nmemb) || m > SIZE_MAX
		|| !(s = size) || s  > SIZE_MAX
		|| !(f = compar))
	{
		errno = EINVAL;
		return (NULL);
	}
	errno ^= errno;
	i = m - 1;
	if ((t = malloc(s)) == NULL)
		return (NULL);
	while (--m)
	{
		j ^= j;
		c ^= c;
		while (j < i)
		{
			if (((*f)((b + (s * i)), (b + (s * j)))) < 0)
			{
				if (!(memcpy(t, (b + (s * i)), s))
					|| !(memcpy((void *)(b + (s * i)), (b + (s * j)), s))
					|| !(memcpy((void *)(b + (s * j)), (const void *)(t), s)))
				{
					free(t);
					return (NULL);
				}
				c++;
			}
			if (j == SIZE_MAX)
			{
				errno = EOVERFLOW;
				free(t);
				return (NULL);
			}
			j++;
		}
		if (!c)
			break ;
		i--;
	}
	free(t);
	return (NULL);
}
