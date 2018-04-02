/*
** ut_umaxdiv.c
**
** Unit tests for umaxdiv function of Undefined-C library
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

#include <libuc/inttypes.h>
#include <libuc/errno.h>

typedef struct			test_s
{
	uintmax_t			numer;
	uintmax_t			denom;
	umaxdiv_t			div;
	int					error;
}						test_t;

int	ut_umaxdiv_interface(int N)
{
	int			i;
	umaxdiv_t	ret;
	int			err;
	test_t		tdat[2] = {	{N, 0, {0, 0}, EINVAL},
							{10, 5, {2, 0}, 0} };

	errno = 0;
	i = 0;
	err = 0xFF;
	while (i < 2)
	{
		ret = umaxdiv((tdat[i]).numer, (tdat[i]).denom);
		if (errno != (tdat[i]).error)
			return (err);
		err--;
		if ((tdat[i]).div.quot != ret.quot)
			return (err);
		err--;
		if ((tdat[i]).div.rem != ret.rem)
			return (err);
		i++;
		err--;
	}
	return (0);
}

int	ut_umaxdiv_validity(int N)
{
	int			i;
	umaxdiv_t	ret;
	int			err;
	test_t		tdat[7] = {	{10, 3, {3, 1}, 0},
							{10, 4, {2, 2}, 0},
							{10, 5, {2, 0}, 0},
							{N, 2, {(N / 2), (N % 2)}, 0},
							{N, 3, {(N / 3), (N % 3)}, 0},
							{N, 5, {(N / 5), (N % 5)}, 0},
							{N, 7, {(N / 7), (N % 7)}, 0} };

	errno = 0;
	i = 0;
	err = 0xFF;
	while (i < 7)
	{
		ret = umaxdiv((tdat[i]).numer, (tdat[i]).denom);
		if (errno)
			return (err);
		err--;
		if ((tdat[i]).div.quot != ret.quot)
			return (err);
		err--;
		if ((tdat[i]).div.rem != ret.rem)
			return (err);
		i++;
		err--;
	}
	return (0);
}

int	ut_umaxdiv_memchk(int N)
{
	uintmax_t	i;
	umaxdiv_t	ret;

	errno = 0;
	i = 1;
	while (i < (uintmax_t)(N))
	{
		ret = umaxdiv(N, i++);
		if (!(ret.quot) && !(ret.rem))
			return (i);
	}
	return (0);
}

int	ut_umaxdiv_timeout(int N)
{
	return (ut_umaxdiv_memchk(N));
}
