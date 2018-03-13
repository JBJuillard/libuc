/*
** slst_rcmp function for Undefined-C library
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
#include <stdlib.h>			/* Dev: a modifier après implantation de calloc */
#include <libuc/limits.h>
#include <libuc/stdlst.h>

int	slst_rcmp(slst_t **lst1,
				slst_t **ptr1,
				slst_t **lst2,
				slst_t **ptr2,
				int (*fcmp)(const void *, const size_t,
									const void *, const size_t))
{
	register slst_t	*tmp1;
	register slst_t	*tmp2;
	register slst_t	**tab1;
	register slst_t	**tab2;
	register int	ret;
	register size_t	i;
	register size_t	j;

	if (!lst1 || !lst2 || (ptr1 && *ptr1) || (ptr2 && *ptr2) || !fcmp)
	{
		errno = EINVAL;
		return (0);
	}
	else if (!*lst1)
		return (INT_MIN);
	else if (!*lst2)
		return (INT_MAX);
	errno = 0;
	tab1 = (slst_t **)(NULL);
	tab2 = (slst_t **)(NULL);
	i = slst_len(lst1);
	i = (i >= (j = slst_len(lst2))) ? i : j;
	if ((tab1 = (slst_t **)calloc(i, sizeof(slst_t *))) == (slst_t **)(NULL)
		|| (tab2 = (slst_t **)calloc(i, sizeof(slst_t *))) == (slst_t **)(NULL))
	{
		if (tab1)
			free((void *)(tab1));
		if (!errno)
			errno = ENOMEM;
		return (0);
	}
	tmp1 = *lst1;
	tmp2 = *lst2;
	j = 0;
	while ((tmp1 || tmp2) && j < i)
	{
		if (tmp1)
		{
			tab1[j] = tmp1;
			tmp1 = tmp1->next;
		}
		else
			tab1[j] = (slst_t *)(NULL);
		if (tmp2)
		{
			tab2[j] = tmp2;
			tmp2 = tmp2->next;
		}
		else
			tab1[j] = (slst_t *)(NULL);
		j++;
	}
	j = i - 1;
	ret = 0;
	while (1)
	{
		if ((tab1[j] && tab2[j]
				&& (ret = (*fcmp)((const void *)((tab1[j])->key),
									(const size_t)((tab1[j])->size),
									(const void *)((tab2[j])->key),
									(const size_t)((tab2[j])->size))))
			|| (!tab1[j] && tab2[j])
			|| (tab1[j] && !tab2[j]))
		{
			if (ptr1)
				*ptr1 = tab1[j];
			if (ptr2)
				*ptr2 = tab2[j];
			free((void *)(tab1));
			free((void *)(tab2));
			if (!ret)
				ret = (tab1[j]) ? INT_MIN : INT_MAX ;
			return (ret);
		}
		if (j == 0)
			break ;
		--j;
	}
	if (ptr1)
		*ptr1 = (slst_t *)(NULL);
	if (ptr2)
		*ptr2 = (slst_t *)(NULL);
	free((void *)(tab1));
	free((void *)(tab2));
	return (0);
}
