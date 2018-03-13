/*
** slst_random function for Undefined-C library
**
** Created: 03/12/2017 by Juillard Jean-Baptiste
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
#include <stdlib.h>			/* Dev: a modifier après implantation de calloc et de free */
#include <libuc/limits.h>
#include <libuc/stdlst.h>

slst_t	*slst_random(slst_t **lst, unsigned int seed)
{
	register slst_t		**tab;
	register slst_t		*tmp;
	register size_t		len;
	register size_t		i;
	register size_t		j;

	errno = 0;
	if (!lst || !seed || seed > UINT_MAX)
	{
		errno = EINVAL;
		return ((slst_t *)(NULL));
	}
	else if (!*lst)
		return ((slst_t *)(NULL));
	if (((len = slst_len(lst)) == 0 && errno)
		|| (tab = (slst_t **)calloc(len, sizeof(slst_t *)))
			== (slst_t **)(NULL))
		return ((slst_t *)(NULL));
	i = 0;
	tmp = *lst;
	while (tmp && i < len)
	{
		tab[i++] = tmp;
		tmp = tmp->next;
	}
	if (tmp || i-- != len)
		return ((slst_t *)(NULL));
	srand(seed);
	while (i > 0)
	{
		if ((j = rand()) >= i)
			j %= i;
		tmp = tab[i];
		tab[i--] = tab[j];
		tab[j] = tmp;
	}
	i = len - 1;
	*lst = (slst_t *)(NULL);
	while (1)
	{
		(tab[i])->next = *lst;
		*lst = tab[i];
		if (i == 0)
			break ;
		i--;
	}
	free((void *)(tab));
	return (*lst);
}
