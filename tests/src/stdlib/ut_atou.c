/*
** ut_atou.c
**
** Unit tests for atou function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/26 by Juillard Jean-Baptiste
** Updated: 2018/03/31 by Juillard Jean-Baptiste
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

typedef struct		test_s
{
	const char		*str;
	unsigned int	ret;
	int				error;
	
}					test_t;

int	ut_atou_interface(int N)
{
	int		i;
	int		err;
	test_t	tdat[4] = {	{(const char *)(NULL), 0, EINVAL},
						{"", 0, 0},
						{"+1", 1, 0},
						{"1", 1, 0} };

	err = 0xff;
	i = 0;
	N = N;
	while (i < 4)
	{
		errno = 0;
		if (atou((tdat[i]).str) != (tdat[i]).ret
			|| errno != (tdat[i]).error)
			return (err);
		i++;
		err--;
	}
	return (0);
}

int	ut_atou_validity(int N)
{
	unsigned int	i;
	char			*s;

	i = 0;
	while (i < (unsigned int)(N))
	{
		errno = 0;
		if (!(s = utoa(i)))
			return (-1);
		if (atou((const char *)(s)) != i
			|| errno)
			return (i + 1);
		i++;
	}
	return (0);
}

int	ut_atou_memchk(int N)
{
	return (ut_atou_validity(N));
}

int	ut_atou_timeout(int N)
{
	return (ut_atou_validity(N));
}
