/*
** ut_isprint.c
**
** Unit tests for isprint function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/22 by Juillard Jean-Baptiste
** Updated: 2018/03/23 by Juillard Jean-Baptiste
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
#include <libuc/ctype.h>
#include <libuc/stdio.h>
#include <libuc/stddef.h>

typedef struct		test_s
{
	int				c1;
	int				c2;
	int				err;
	int				ret;
}					test_t;

int		ut_isprint_interface(int N)
{
	int			err;
	size_t		i;
	int			j;
	auto test_t	tdat[4] ={	{(-N - 1), (EOF - 1), EINVAL, 0},
							{(EOF + 1), -1, EINVAL, 0},
							{0x100, N, EINVAL, 0},
							{EOF, EOF, 0, 0}};

	err = 0xFF;
	i ^= i;
	while (i < 4)
	{
		j = (tdat[i]).c1;
		while (j <= (tdat[i]).c2)
		{
			if (isprint(j) != (tdat[i]).ret
				|| errno != (tdat[i]).err)
				return (err);
			j++;
		}
		i++;
		err--;
	}
	return (0);
}

int		ut_isprint_validity(int N)
{

	int			err;
	size_t		i;
	int			j;
	auto test_t	tdat[3] ={	{0x0, 0x1F, 0, 0},
							{0x20, 0x7E, 0, 1},
							{0x7F, 0xFF, 0, 0}};

	err = 0xFF;
	N = N;
	i ^= i;
	while (i < 3)
	{
		j = (tdat[i]).c1;
		while (j <= (tdat[i]).c2)
		{
			if (isprint(j) != (tdat[i]).ret
				|| errno != (tdat[i]).err)
				return (err);
			j++;
		}
		i++;
		err--;
	}
	return (0);
}

int		ut_isprint_memchk(int N)
{
	int	i;

	i ^= i;
	while (i < N)
		isprint(i++);
	return (0);
}

int		ut_isprint_timeout(int N)
{
	return (ut_isprint_memchk(N));
}
