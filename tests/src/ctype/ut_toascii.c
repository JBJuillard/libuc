/*
** ut_toascii.c
**
** Unit tests for toascii function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/22 by Juillard Jean-Baptiste
** Updated: 2018/04/04 by Juillard Jean-Baptiste
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

int		ut_toascii_interface(int N)
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
			if (toascii(j) != (((j < 0x0 || j > 0xFF) && (j != EOF)) ? (0) : ((j != EOF && j & 0x80) ? (j ^ 0x80) : (j)))
				|| errno != (tdat[i]).err)
				return (err);
			j++;
		}
		i++;
		err--;
	}
	return (0);
}

int		ut_toascii_validity(int N)
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
			if (toascii(j) != (((j < 0x0 || j > 0xFF) && (j != EOF)) ? (0) : ((j & 0x80) ? (j ^ 0x80) : (j)))
				|| errno != (tdat[i]).err)
				return (err);
			j++;
		}
		i++;
		err--;
	}
	return (0);
}

int		ut_toascii_memchk(int N)
{
	int	i;

	i ^= i;
	while (i < N)
		toascii(i++);
	return (0);
}

int		ut_toascii_timeout(int N)
{
	return (ut_toascii_memchk(N));
}
