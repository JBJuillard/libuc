/*
** ut_tolower.c
**
** Unit tests for tolower function of Undefined-C library
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
}					test_t;

int		ut_tolower_interface(int N)
{
	int			err;
	size_t		i;
	int			j;
	auto test_t	tdat[4] ={	{(-N - 1), (EOF - 1), EINVAL},
							{(EOF + 1), -1, EINVAL},
							{0x100, N, EINVAL},
							{EOF, EOF, 0}};

	err = 0xFF;
	i ^= i;
	while (i < 4)
	{
		j = (tdat[i]).c1;
		while (j <= (tdat[i]).c2)
		{
			if (tolower(j) != (((j < 0x0 || j > 0xFF) && (j != EOF)) ? (0) : ((j >= (int)('A') && (j <= (int)('Z'))) ? (j + 0x20) : (j)))
				|| errno != (tdat[i]).err)
				return (err);
			j++;
		}
		i++;
		err--;
	}
	return (0);
}

int		ut_tolower_validity(int N)
{

	int			err;
	size_t		i;
	int			j;
	auto test_t	tdat[2] ={	{0x0, 0x7F, 0},
							{0x80, 0xFF, 0}};

	err = 0xFF;
	N = N;
	i ^= i;
	while (i < 2)
	{
		j = (tdat[i]).c1;
		while (j <= (tdat[i]).c2)
		{
			if (tolower(j) != (((j < 0x0 || j > 0xFF) && (j != EOF)) ? (0) : ((j >= (int)('A') && (j <= (int)('Z'))) ? (j + 0x20) : (j)))
				|| errno != (tdat[i]).err)
				return (err);
			j++;
		}
		i++;
		err--;
	}
	return (0);
}

int		ut_tolower_memchk(int N)
{
	int	i;

	i ^= i;
	while (i < N)
		tolower(i++);
	return (0);
}

int		ut_tolower_timeout(int N)
{
	return (ut_tolower_memchk(N));
}
