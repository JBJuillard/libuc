/*
** Test for slst_xtrck function of Undefined-C library
**
** Created: 17/01/2017 10:00:00 by Juillard Jean-Baptiste
** Updated: 17/01/2017 10:00:00 by Juillard Jean-Baptiste
*/

#include <stdlib.h>
#include <stdint.h>
#include "stdlst.h"
#include "test.h"

typedef struct	test_s
{
	int	lst;
	int	key;
	size_t	size;
	void	*f;
	int	err;
}		test_t;


int	ut_slst_xtrck_interface(int N)
{
	slst_t		*lst;
	slst_t		**lptr;
	void		*key;
	int		err;
	int		i;
	static test_t	ut_list[7] = {	{ 0, 1, sizeof(long long), ((void *)(&_ocmp)), EINVAL },
					{ 1, 0, sizeof(long long), ((void *)(&_ocmp)), EINVAL },
					{ 1, 1, 0, ((void *)(&_ocmp)), EINVAL },
					{ 1, 1, (SIZE_MAX + 1), ((void *)(&_ocmp)), EINVAL },
					{ 1, 1, sizeof(long long), NULL, EINVAL },
					{ 1, 1, sizeof(long long), ((void *)(&_ocmp)), 0 },
					{ 1, 1, sizeof(long long), ((void *)(&_ocmp)), 0 }};

	i = 0;
	err = 0xFF;
	while (i < 7)
	{
		lst = (slst_t *)(NULL);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (slst_t **)(NULL);
	        if ((lst = _gen_slst(0, N, 1)) == (slst_t *)(NULL))
		{
			if (lst)
				slst_purge(&lst, &_ofree);
			return (errno);
		}
		if ((ut_list[i]).key)
		{
			if ((key = malloc(sizeof(long long))) == NULL)
			{
				slst_purge(&lst, &_ofree);
				return (errno);
			}
			*((long long *)(key)) = (N / 2);
		}
		else
			key = NULL;
		errno = 0;
		slst_xtrck(lptr, key, (ut_list[i]).size, (int (*)(const void *, const size_t, const void *, const size_t))((ut_list[i]).f));
		if (key)
			free(key);
		if (errno != (ut_list[i]).err)
		{
			slst_purge(&lst, &_ofree);
			return (err);
		}
		slst_purge(&lst, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_xtrck_memchk(int N)
{
	slst_t	*lst;
	slst_t	*tmp;
	void	*i;

	errno = 0;
	if ((lst = _gen_slst(0, N, 1)) == (slst_t *)(NULL)
		|| (i = malloc(sizeof(long long))) == NULL)
	{
		if (lst)
			slst_purge(&lst, &_ofree);
		return (errno);
	}
	while (lst && N >= 0)
	{
		*((long long *)(i)) = N--;
		if (!(tmp = slst_xtrck(&lst, i, sizeof(long long), _ocmp)) || errno)
		{
			slst_purge(&lst, &_ofree);
			free(i);
			if (tmp)
			{
				free(tmp->key);
				free(tmp);
			}
			if (errno)
				return (errno);
			return (0xFF);
		}
		free(tmp->key);
		free(tmp);
	}
	free(i);
	return (0);
}

int	ut_slst_xtrck_timeout(int N)
{
	return (ut_slst_xtrck_memchk(N));
}
