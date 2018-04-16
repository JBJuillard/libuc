/*
** tsearch.c
**
** tsearch function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/04/12 by Juillard Jean-Baptiste
** Updated: 2018/04/13 by Juillard Jean-Baptiste
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

#include <libuc/search.h>
#include <libuc/errno.h>
#include <libuc/stdlib.h>

typedef struct		node_s
{
	void			*key;
	struct node_s	*left;
	struct node_s	*right;
}					node_t;

void	*tsearch(const void *key, void **rootp,
					int (*compar)(const void *,const void *))
{
	register node_t		*ptr;
	register void		*ret;

	if (!key || !rootp || !compar)
	{
		errno = EINVAL;
		return (NULL);
	}
	errno = 0;
	if (*rootp)
	{
		ptr = *((node_t **)(rootp));
		if (!((*compar)(key, (const void *)(ptr->key))))
			return (ptr->key);
		else if ((ret = tsearch(key, (void **)(&(ptr->left)), compar)))
			return (ret);
		else if ((ret = tsearch(key, (void **)(&(ptr->right)), compar)))
			return (ret);
	}
	return (NULL);
}
