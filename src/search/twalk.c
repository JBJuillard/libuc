/*
** twalk.c
**
** twalk function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/04/13 by Juillard Jean-Baptiste
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

typedef struct		node_s
{
	void			*key;
	struct node_s	*left;
	struct node_s	*right;
}					node_t;

void	twalk(const void *root, void (*action)(const void *nodep,
												const VISIT which,
												const int depth))
{
	register node_t		*ptr;
	static int			dpth = 0;

	if (!root || !action)
	{
		errno = EINVAL;
		return ;
	}
	errno = 0;
	ptr = *((node_t *)(root));
	if (ptr->left || ptr->right)
	{
		(*action)((const void *)(ptr), preorder, dpth);
		if (ptr->left)
		{
			dpth++;
			twalk((const void *)(ptr->left), action);
			dpth--;
		}
		(*action)((const void *)(ptr), postorder, dpth);
		if (ptr->right)
		{
			dpth++;
			twalk((const void *)(ptr->right), action);
			dpth--;
		}
		(*action)((const void *)(ptr), endorder, dpth);
	}
	else
		(*action)((const void *)(ptr), leaf, dpth);
}
