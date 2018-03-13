/*
** slst_rrch function for Undefined-C library
**
** Created: 12/28/2016 by Juillard Jean-Baptiste
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

#include <libuc/stddef.h>
#include <libuc/errno.h>
#include <libuc/stdint.h>
#include <stdlib.h>			/* Dev: a modifier après implantation de calloc */
#include <libuc/stdlst.h>

slst_t	*slst_rrch(slst_t **lst,
					const void *key,
					const size_t size,
					int (*fcmp)(const void *, const size_t,
								const void *, const size_t))
{
	register slst_t	*ptr;
	register slst_t	**tab;
	register size_t	i;


	if (!lst || !key || !size || size > SIZE_MAX || !fcmp)
	{
		errno = EINVAL;
		return ((slst_t *)(NULL));
	}
	errno = 0;
	if (((i = slst_len(lst)) == 0 && errno)
		|| (tab = (slst_t **)calloc(i, sizeof(slst_t *))) == (slst_t **)(NULL))
		return ((slst_t *)(NULL));
	i = 0;
	ptr = *lst;
	while (ptr)
	{
		tab[i++] = ptr;
		ptr = ptr->next;
	}
	--i;
	while (1)
	{
		if (!(*fcmp)(key, size,
					 (const void *)((tab[i])->key), (const size_t)((tab[i])->size)))
		{
			ptr = tab[i];
			break ;
		}
		if (i == 0)
			break ;
	    i--;
	}
	free((void *)(tab));
	return (ptr);
}
