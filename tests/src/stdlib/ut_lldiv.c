/*
** ut_lldiv.c
**
** Unit tests for lldiv function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/26 by Juillard Jean-Baptiste
** Updated: 2018/03/26 by Juillard Jean-Baptiste
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

#include <libuc/stdlib.h>
#include <libuc/errno.h>

typedef struct			test_s
{
	long long int		numer;
	long long int		denom;
	lldiv_t				lldiv;
	int					error;
}						test_t;

int	ut_lldiv_interface(int N)
{
	int		i;
	lldiv_t	ret;
	int		err;
	test_t	tdat[2] = {	{N, 0, {0, 0}, EINVAL},
						{10, 5, {2, 0}, 0} };

	errno = 0;
	i = 0;
	err = 0xFF;
	while (i < 2)
	{
		ret = lldiv((tdat[i]).numer, (tdat[i]).denom);
		if (errno != (tdat[i]).error)
			return (err);
		err--;
		if ((tdat[i]).lldiv.quot != ret.quot)
			return (err);
		err--;
		if ((tdat[i]).lldiv.rem != ret.rem)
			return (err);
		i++;
		err--;
	}
	return (0);
}

int	ut_lldiv_validity(int N)
{
	int		i;
	lldiv_t	ret;
	int		err;
	test_t	tdat[7] = {	{10, 3, {3, 1}, 0},
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
		ret = lldiv((tdat[i]).numer, (tdat[i]).denom);
		if (errno)
			return (err);
		err--;
		if ((tdat[i]).lldiv.quot != ret.quot)
			return (err);
		err--;
		if ((tdat[i]).lldiv.rem != ret.rem)
			return (err);
		i++;
		err--;
	}
	return (0);
}

int	ut_lldiv_memchk(int N)
{
	long long int	i;
	lldiv_t			ret;

	errno = 0;
	i = 1;
	while (i <= N)
	{
		ret = lldiv((long long int)(N), i++);
		if (!(ret.quot) && !(ret.rem))
			return (i);
	}
	return (0);
}

int	ut_lldiv_timeout(int N)
{
	return (ut_lldiv_memchk(N));
}
