/*
** slst_head.c
**
** slst_head function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2016/12/28 by Juillard Jean-Baptiste
** Updated: 2018/03/14 by Juillard Jean-Baptiste
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
#include <stdlib.h>			/* Dev: A remplacer apres implantaion de malloc */
#include <libuc/stdint.h>
#include <libuc/stdlst.h>

mslst_t	*slst_head(slst_t **lst, size_t n)
{
	register slst_t		*ptr;
	register size_t		i;
	register mslst_t	*head;
	auto mslst_t		*tmp;
	register int		err;

	errno = 0;
	if (!lst || !n || n > SIZE_MAX)
	{
		errno = EINVAL;
		return ((mslst_t *)(NULL));
	}
	else if (!*lst)
		return ((mslst_t *)(NULL));
	ptr = *lst;
	i = 0;
	head = (mslst_t *)(NULL);
	while (i < n)
	{
		if ((tmp = (mslst_t *)malloc(sizeof(mslst_t))) == (mslst_t *)(NULL))
		{
			if (!errno)
				errno = ENOMEM;
			if (head)
			{
				tmp = head->next;
				head->next = (mslst_t *)(NULL);
				err = errno;
				mslst_purge(&tmp);
				errno = err;
			}
			return (mslst_t *)(NULL);
		}
		tmp->kptr = ((ptr) ? &(ptr->key) : (void **)(NULL));
		tmp->sptr = ((ptr) ? &(ptr->size) : (size_t *)(NULL));
		if (head)
		{
			tmp->next = head->next;
			head->next = tmp;
		}
		else
			tmp->next = tmp;
		if (ptr)
			ptr = ptr->next;
		head = tmp;
		i++;
	}
	tmp = head->next;
	head->next = (mslst_t *)(NULL);
	return (tmp);
}
