/*
** insque.c
**
** insque function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/04/12 by Juillard Jean-Baptiste
** Updated: 2018/04/12 by Juillard Jean-Baptiste
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

void	insque(void *elem, void *prev)
{
	register struct qelem	*e;
	register struct qelem	*p;
	register struct qelem	*n;

	if (!elem || !prev)
	{
		errno = EINVAL;
		return ;
	}
	errno = 0;
	e = (struct qelem *)(elem);
	p = (struct qelem *)(prev);
	if (p)
	{
		n = p->forw;
		if (n)
			n->q_back = e;
		e->q_forw = n;
		e->q_back = p;
	}
	else
	{
		e->q_forw = (struct qelem *)(NULL);
		e->q_back = (struct qelem *)(NULL);
	}
}
