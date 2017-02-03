/*
** Test for slst_xtrcp function of Undefined-C library
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
	int	elm;
	int	err;
}		test_t;


int	ut_slst_xtrcp_interface(int N)
{
	slst_t		*lst;
	slst_t		**lptr;
	slst_t		*elm;
	int		err;
	int		i;
	static test_t	ut_list[4] = {	{ 0, 1, EINVAL },
					{ 1, 0, EINVAL },
					{ 1, 1, 0 },
					{ 1, 1, 0 }};

	i = 0;
	err = 0xFF;
	while (i < 4)
	{
		if ((lst = _gen_slst(0, N, 1)) == (slst_t *)(NULL))
			return (errno);
		if ((ut_list[i]).lst)
			lptr = &lst;
		else
			lptr = (slst_t **)(NULL);
	        if ((ut_list[i]).elm)
			elm = lst;
		else
			elm = (slst_t *)(NULL);
		errno = 0;
		if ((elm = slst_xtrcp(lptr, elm)) == (slst_t *)(NULL)
			&& errno != (ut_list[i]).err)
		{
			slst_purge(&lst, &_ofree);
			if (elm)
			{
				free(elm->key);
				free((void *)(elm));
			}
			return (err);
		}
		if (elm)
		{
			free(elm->key);
			free((void *)(elm));
		}
		slst_purge(&lst, &_ofree);
		i++;
		err--;
	}
	return (0);
}

int	ut_slst_xtrcp_memchk(int N)
{
	slst_t	*lst;
	slst_t	*tmp;

	errno = 0;
	if ((lst = _gen_slst(0, N, 1)) == (slst_t *)(NULL))
		return (errno);
	while (lst && N-- >= 0)
	{
		if (!(tmp = slst_xtrcp(&lst, lst)) || errno)
		{
			slst_purge(&lst, &_ofree);
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
	return (0);
}

int	ut_slst_xtrcp_timeout(int N)
{
	return (ut_slst_xtrcp_memchk(N));
}
