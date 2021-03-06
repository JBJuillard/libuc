/*
** ut_strlen.c
**
** Unit tests for strlen function of Undefined-C library
**
** By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
**
** Created: 2018/04/15 by Juillard Jean-Baptiste
** Updated: 2018/04/15 by Juillard Jean-Baptiste
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

#include <libuc/string.h>
#include <stdlib.h>
#include <libuc/errno.h>

typedef struct		test_s
{
	char			*str;
	size_t			ret;
	int				err;
}					test_t;

int	ut_strlen_interface(int N)
{
	int		i;
	int		err;
	test_t	tdat[2] = {	{(char *)(NULL), 0, EINVAL},
						{"0123456789", 10, 0} };

	i ^= i;
	err = 0xff;
	N = N;
	while (i < 2)
	{
		if (strlen((tdat[i]).str) != (tdat[i]).ret
			|| (tdat[i]).err != errno)
			return (err);
		++i;
		--err;
	}
	return (0);
}

int	ut_strlen_validity(int N)
{
	size_t	i;
	char	*str;

	if ((str = (char *)malloc((N + 1) * sizeof(char))) == (char *)(NULL))
		return (0xff);
	i ^= i;
	srand(N);
	while (i < (size_t)(N))
		str[i++] = (rand() % 26) + 'a';
	str[N] = '\0';
	if (strlen(str) != (size_t)(N))
	{
		free((void *)(str));
		return (0xfe);
	}
	free((void *)(str));
	return (0);
}

int	ut_strlen_memchk(int N)
{
	return (ut_strlen_validity(N));
}

int	ut_strlen_timeout(int N)
{
	return (ut_strlen_validity(N));
}
