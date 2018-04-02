/*
** ut_strtoul.c
**
** Unit tests for strtoul function of Undefined-C library
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

typedef struct			test_s
{
	const char			*str;
	char				**end;
	char				*endval;
	unsigned long int	ret;
	int					error;
	
}						test_t;

int	ut_strtoul_interface(int N)
{
	int		i;
	int		err;
	char	*end;
	test_t	tdat[4] = {	{(const char *)(NULL), (char **)(NULL), (char *)(NULL), 0, EINVAL},
						{"", &end, (char *)((tdat[1]).str), 0, 0},
						{"+1", &end, (char *)((tdat[2]).str + 2), 1, 0},
						{"1", &end, (char *)((tdat[3]).str + 1), 1, 0} };

	err = 0xff;
	i = 0;
	N = N;
	while (i < 4)
	{
		errno = 0;
		end = (char *)(NULL);
		if (strtoul((tdat[i]).str, (tdat[i]).end, 10) != (tdat[i]).ret
			|| (tdat[i]).endval != end
			|| errno != (tdat[i]).error)
			return (err);
		i++;
		err--;
	}
	return (0);
}

int	ut_strtoul_validity(int N)
{
	unsigned long int	i;
	char				*s;

	i = 0;
	while (i < (unsigned long int)(N))
	{
		errno = 0;
		if (!(s = ultostr(i, 10, 0)))
			return (-1);
		if (strtoul((const char *)(s), (char **)(NULL), 10) != i
			|| errno)
			return (i + 1);
		i++;
	}
	return (0);
}

int	ut_strtoul_memchk(int N)
{
	return (ut_strtoul_validity(N));
}

int	ut_strtoul_timeout(int N)
{
	return (ut_strtoul_validity(N));
}
