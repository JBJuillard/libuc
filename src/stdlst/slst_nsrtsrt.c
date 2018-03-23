/*
** slst_nsrtsrt.c
**
** slst_nsrtsrt function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/03/09 by Juillard Jean-Baptiste
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

#include <libuc/errno.h>
#include <libuc/stdlib.h>
#include <libuc/stdlst.h>

slst_t	*slst_nsrtsrt(slst_t **lst, int (*fcmp)(const void *, const size_t,
												const void *, const size_t))
{
	register slst_t	*tlst;
	register slst_t	**ptr;
	register slst_t	*cur;

	errno = 0;
	if (!lst || !fcmp)
	{
		errno = EINVAL;
		return ((slst_t *)(NULL));
	}
	else if (!*lst)
		return ((slst_t *)(NULL));
	tlst = *lst;
	*lst = (slst_t*)(NULL);
	while (tlst)
	{
		cur = tlst;
		tlst = tlst->next;
		ptr = lst;
		while (*ptr)
		{
			if ((*fcmp)((const void *)(cur->key),
						(const size_t)(cur->size),
						(const void *)((*ptr)->key),
						(const size_t)((*ptr)->size)) <= 0)
				break ;
			ptr = &((*ptr)->next);
		}
		cur->next = *ptr;
		*ptr = cur;
	}
	return (*lst);
}
