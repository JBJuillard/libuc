/*
** ut_abs.c
**
** Unit tests for abs function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/03/23 by Juillard Jean-Baptiste
** Updated: 2018/03/25 by Juillard Jean-Baptiste
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
#include <libuc/limits.h>

typedef struct		err_s
{
	int				n;
	int				ret;
	int				err;
}					err_t;

int	ut_abs_interface(int N)
{
	int		i;
	int		error;
	err_t	tdat[2] = {	{INT_MIN, INT_MIN, ERANGE},
						{INT_MAX, INT_MAX, 0}};

	error = 0xFF;
	i = 0;
	N = N;
	while (i < 2)
	{
		if (abs((tdat[i]).n) != (tdat[i]).ret
			|| errno != (tdat[i]).err)
			return (error);
		i++;
		error--;
	}
	return (0);
}

int	ut_abs_validity(int N)
{
	int	i;

	i = -INT_MAX;
	N = N;
	while (1)
	{
		if (i < 0 && abs(i) != -i)
			return (-i);
		else if (!i && !abs(i))
			return (INT_MIN);
		else if (i > 0 && abs(i) != i)
			return (i);
		if (i == INT_MAX)
			break ;
		i++;
	}
	return (0);
}

int	ut_abs_memchk(int N)
{
	int	i;

	i = 1;
	while (i <= N)
	{
		if (abs(i) != i)
			return (((!i) ? (INT_MIN) : (i)));
		if (i == INT_MAX)
			break ;
		i++;
	}
	return (0);
}

int	ut_abs_timeout(int N)
{
	return (ut_abs_memchk(N));
}
