/*
** ut_strtoi.c
**
** Unit tests for strtoimax function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/31 by Juillard Jean-Baptiste
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
#include <libuc/inttypes.h>

typedef struct		test_s
{
	const char		*str;
	char			**end;
	char			*endval;
	intmax_t		ret;
	int				error;
	
}					test_t;

int	ut_strtoimax_interface(int N)
{
	int		i;
	int		err;
	char	*end;
	test_t	tdat[5] = {	{(const char *)(NULL), (char **)(NULL), (char *)(NULL), 0, EINVAL},
						{"", &end, (char *)((tdat[1]).str), 0, 0},
						{"-1", &end, (char *)((tdat[2]).str + 2), -1, 0},
						{"+1", &end, (char *)((tdat[3]).str + 2), 1, 0},
						{"1", &end, (char *)((tdat[4]).str + 1), 1, 0} };

	err = 0xff;
	i = 0;
	N = N;
	while (i < 5)
	{
		errno = 0;
		end = (char *)(NULL);
		if (strtoimax((tdat[i]).str, (tdat[i]).end, 10) != (tdat[i]).ret
			|| end != (tdat[i]).endval
			|| errno != (tdat[i]).error)
			return (err);
		i++;
		err--;
	}
	return (0);
}

int	ut_strtoimax_validity(int N)
{
	intmax_t	i;
	char		*s;

	i = 0;
	while (i < N)
	{
		errno = 0;
		s = (char *)(NULL);
		if (strtoimax((const char *)(s = ((char *)imaxtostr(i, 10, 0))), (char **)(NULL), 10) != i
			|| errno)
			return (i + 1);
		i++;
	}
	return (0);
}

int	ut_strtoimax_memchk(int N)
{
	return (ut_strtoimax_validity(N));
}

int	ut_strtoimax_timeout(int N)
{
	return (ut_strtoimax_validity(N));
}
