/*
** ut_atoll.c
**
** Unit tests for atoll function of Undefined-C library
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
	long long int	ret;
	int				error;
	
}					test_t;

int	ut_atoll_interface(int N)
{
	int		i;
	int		err;
	test_t	tdat[5] = {	{(const char *)(NULL), 0, EINVAL},
						{"", 0, 0},
						{"-1", -1, 0},
						{"+1", 1, 0},
						{"1", 1, 0} };

	err = 0xff;
	i = 0;
	N = N;
	while (i < 5)
	{
		errno = 0;
		if (atoll((tdat[i]).str) != (tdat[i]).ret
			|| errno != (tdat[i]).error)
			return (err);
		i++;
		err--;
	}
	return (0);
}

int	ut_atoll_validity(int N)
{
	long long int	i;
	char			*s;

	i = 0;
	while (i < (long long int)(N))
	{
		errno = 0;
		if ((s = lltoa(i)) == (char *)(NULL)
			|| atoll((const char *)(s)) != i
			|| errno)
			return ((int)(i));
		i++;
	}
	return (0);
}

int	ut_atoll_memchk(int N)
{
	return (ut_atoll_validity(N));
}

int	ut_atoll_timeout(int N)
{
	return (ut_atoll_validity(N));
}
