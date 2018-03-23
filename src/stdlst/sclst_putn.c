/*
** sclst_putn.c
**
** sclst_putn function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2017/03/08 by Juillard Jean-Baptiste
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
#include <libuc/stdint.h>
#include <stdlib.h>			/* Dev: a modifier après implantation de malloc */
#include <libuc/stdlst.h>

sclst_t	*sclst_putn(sclst_t **lst, void *key, size_t size, size_t n)
{
	register sclst_t	*ptr;
	register sclst_t	**addr;
	register size_t		i;
	register sclst_t	*tmp;

	if (!lst || !key || !size || size > SIZE_MAX || !n || n > SIZE_MAX)
	{
		errno = EINVAL;
		return ((sclst_t *)(NULL));
	}
	errno = 0;
	if (!*lst)
	{
		ptr = (sclst_t *)(NULL);
		addr = lst;
	}
	else
	{
		ptr = (*lst)->next;
		addr = &((*lst)->next);
	}
	i = 1;
	while (ptr && i < n)
	{
		if (ptr == *lst)
			break ;
		addr = &(ptr->next);
		ptr = ptr->next;
		i++;
	}
	if (i != n)
	{
		errno = ERANGE;
		return ((sclst_t *)(NULL));
	}
	if ((tmp = (sclst_t *)malloc(sizeof(sclst_t))) == (sclst_t *)(NULL))
	{
		if (!errno)
			errno = ENOMEM;
		return ((sclst_t *)(NULL));
	}
	tmp->key = key;
	tmp->size = size;
	if (*addr)
		tmp->next = *addr;
	else
		tmp->next = tmp;
	*addr = tmp;
	return (tmp);
}
