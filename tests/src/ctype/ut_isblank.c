/*
** ut_isblank.c
**
** Unit tests for isblank function of Undefined-C library
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

int		ut_isblank_interface(int N)
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
			if (isblank(j) != (tdat[i]).ret
				|| errno != (tdat[i]).err)
				return (err);
			j++;
		}
		i++;
		err--;
	}
	return (0);
}

int		ut_isblank_validity(int N)
{

	int			err;
	size_t		i;
	int			j;
	auto test_t	tdat[5] ={	{0x0, 0x8, 0, 0},		/* '0' a '\b' */
							{0x9, 0x9, 0, 1},		/* '\t' (tabulation) */
							{0xA, 0x1F, 0, 0},		/* '\n' to '\x1F' */
							{0x20, 0x20, 0, 1},		/* ' ' (space) */
							{0x21, 0xFF, 0, 0}};	/* '!' to '\xFF' */

	err = 0xFF;
	N = N;
	i ^= i;
	while (i < 5)
	{
		j = (tdat[i]).c1;
		while (j <= (tdat[i]).c2)
		{
			if (isblank(j) != (tdat[i]).ret
				|| errno != (tdat[i]).err)
				return (err);
			j++;
		}
		i++;
		err--;
	}
	return (0);
}

int		ut_isblank_memchk(int N)
{
	int	i;

	i ^= i;
	while (i < N)
		isblank(i++);
	return (0);
}

int		ut_isblank_timeout(int N)
{
	return (ut_isblank_memchk(N));
}
