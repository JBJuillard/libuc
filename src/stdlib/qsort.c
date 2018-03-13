/*
** qsort.c
**
** qsort function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/02/25 by Juillard Jean-Baptiste
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

#include <libuc/errno.h>
#include <libuc/stdlib.h>
#include <libuc/string.h>
#include <libuc/stdint.h>

void	qsort(void *base, size_t nmemb, size_t size,
				int (*compar)(const void *, const void *))
{
	register size_t		i;
	register size_t		j;
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
		return ;
	}
	errno ^= errno;
	i = m - 1;
	if ((t = malloc(s)) == NULL)
		return ;
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
					return ;
				}
				c++;
			}
			if (j == SIZE_MAX)
			{
				errno = EOVERFLOW;
				free(t);
				return ;
			}
			j++;
		}
		if (!c)
			break ;
		i--;
	}
	free(t);
	return ;
}
