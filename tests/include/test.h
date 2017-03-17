/*
** Header file for units test of Undefined-C library
**
** Created: 28/01/2017 by Juillard Jean-Baptiste
** Updated: 02/06/2017 by Juillard Jean-Baptiste
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License as
** published by the Free Software Foundation; either version 3, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; see the file LICENSE.  If not, write to
** the Free Software Foundation, Inc., 51 Franklin Street, Fifth
** Floor, Boston, MA 02110-1301, USA.
*/

#ifndef TEST_H
# define	TEST_H			1

# include	"stdlst.h"

int		get_int(char *str);

void	_ofree(void *key, size_t size);
int		_ocmp(const void *k1, const size_t s1, const void *k2, const size_t s2);
void	*_ocpy(void *key, size_t size);
int		_ofunc(void **key, size_t *size);
int		_oprint(void **k, size_t *s);

/*
** Non-Ordered Simply Linked List (slst_t)
*/
slst_t	*_gen_slst(size_t start, size_t end, size_t step);
/***** slst_newelm *****/
int		ut_slst_newelm_interface(int N);
int		ut_slst_newelm_memchk(int N);
int		ut_slst_newelm_timeout(int N);
/***** slst_delelm *****/
int		ut_slst_delelm_interface(int N);
int		ut_slst_delelm_memchk(int N);
int		ut_slst_delelm_timeout(int N);
/***** slst_isempty *****/
int		ut_slst_isempty_interface(int N);
int		ut_slst_isempty_memchk(int N);
int		ut_slst_isempty_timeout(int N);
/***** slst_len *****/
int		ut_slst_len_interface(int N);
int		ut_slst_len_memchk(int N);
int		ut_slst_len_timeout(int N);
/***** slst_previous *****/
int		ut_slst_previous_interface(int N);
int		ut_slst_previous_memchk(int N);
int		ut_slst_previous_timeout(int N);
/***** slst_next *****/
int		ut_slst_next_interface(int N);
int		ut_slst_next_memchk(int N);
int		ut_slst_next_timeout(int N);
/***** slst_head *****/
int		ut_slst_head_interface(int N);
int		ut_slst_head_memchk(int N);
int		ut_slst_head_timeout(int N);
/***** slst_tail *****/
int		ut_slst_tail_interface(int N);
int		ut_slst_tail_memchk(int N);
int		ut_slst_tail_timeout(int N);
/***** slst_put *****/
int		ut_slst_put_interface(int N);
int		ut_slst_put_memchk(int N);
int		ut_slst_put_timeout(int N);
/***** slst_putn *****/
int		ut_slst_putn_interface(int N);
int		ut_slst_putn_memchk(int N);
int		ut_slst_putn_timeout(int N);
/***** slst_get *****/
int		ut_slst_get_interface(int N);
int		ut_slst_get_memchk(int N);
int		ut_slst_get_timeout(int N);
/***** slst_getn *****/
int		ut_slst_getn_interface(int N);
int		ut_slst_getn_memchk(int N);
int		ut_slst_getn_timeout(int N);
/***** slst_del *****/
int		ut_slst_del_interface(int N);
int		ut_slst_del_memchk(int N);
int		ut_slst_del_timeout(int N);
/***** slst_deln *****/
int		ut_slst_deln_interface(int N);
int		ut_slst_deln_memchk(int N);
int		ut_slst_deln_timeout(int N);
/***** slst_delp *****/
int		ut_slst_delp_interface(int N);
int		ut_slst_delp_memchk(int N);
int		ut_slst_delp_timeout(int N);
/***** slst_delk *****/
int		ut_slst_delk_interface(int N);
int		ut_slst_delk_memchk(int N);
int		ut_slst_delk_timeout(int N);
/***** slst_purge *****/
int		ut_slst_purge_interface(int N);
int		ut_slst_purge_memchk(int N);
int		ut_slst_purge_timeout(int N);
/***** slst_nsrt *****/
int		ut_slst_nsrt_interface(int N);
int		ut_slst_nsrt_memchk(int N);
int		ut_slst_nsrt_timeout(int N);
/***** slst_nsrtn *****/
int		ut_slst_nsrtn_interface(int N);
int		ut_slst_nsrtn_memchk(int N);
int		ut_slst_nsrtn_timeout(int N);
/***** slst_nsrtp *****/
int		ut_slst_nsrtp_interface(int N);
int		ut_slst_nsrtp_memchk(int N);
int		ut_slst_nsrtp_timeout(int N);
/***** slst_nsrtk *****/
int		ut_slst_nsrtk_interface(int N);
int		ut_slst_nsrtk_memchk(int N);
int		ut_slst_nsrtk_timeout(int N);
/***** slst_xtrc *****/
int		ut_slst_xtrc_interface(int N);
int		ut_slst_xtrc_memchk(int N);
int		ut_slst_xtrc_timeout(int N);
/***** slst_xtrcn *****/
int		ut_slst_xtrcn_interface(int N);
int		ut_slst_xtrcn_memchk(int N);
int		ut_slst_xtrcn_timeout(int N);
/***** slst_xtrcp *****/
int		ut_slst_xtrcp_interface(int N);
int		ut_slst_xtrcp_memchk(int N);
int		ut_slst_xtrcp_timeout(int N);
/***** slst_xtrck *****/
int		ut_slst_xtrck_interface(int N);
int		ut_slst_xtrck_memchk(int N);
int		ut_slst_xtrck_timeout(int N);
/***** slst_rch *****/
int		ut_slst_rch_interface(int N);
int		ut_slst_rch_memchk(int N);
int		ut_slst_rch_timeout(int N);
/***** slst_rrch *****/
int		ut_slst_rrch_interface(int N);
int		ut_slst_rrch_memchk(int N);
int		ut_slst_rrch_timeout(int N);
/***** slst_xrch *****/
int		ut_slst_xrch_interface(int N);
int		ut_slst_xrch_memchk(int N);
int		ut_slst_xrch_timeout(int N);
/***** slst_rxrch *****/
int		ut_slst_rxrch_interface(int N);
int		ut_slst_rxrch_memchk(int N);
int		ut_slst_rxrch_timeout(int N);
/***** slst_cmp *****/
int		ut_slst_cmp_interface(int N);
int		ut_slst_cmp_memchk(int N);
int		ut_slst_cmp_timeout(int N);
/***** slst_rcmp *****/
int		ut_slst_rcmp_interface(int N);
int		ut_slst_rcmp_memchk(int N);
int		ut_slst_rcmp_timeout(int N);
/***** slst_diff *****/
int		ut_slst_diff_interface(int N);
int		ut_slst_diff_memchk(int N);
int		ut_slst_diff_timeout(int N);
/***** slst_rdiff *****/
int		ut_slst_rdiff_interface(int N);
int		ut_slst_rdiff_memchk(int N);
int		ut_slst_rdiff_timeout(int N);
/***** slst_cpy *****/
int		ut_slst_cpy_interface(int N);
int		ut_slst_cpy_memchk(int N);
int		ut_slst_cpy_timeout(int N);
/***** slst_rcpy *****/
int		ut_slst_rcpy_interface(int N);
int		ut_slst_rcpy_memchk(int N);
int		ut_slst_rcpy_timeout(int N);
/***** slst_cat *****/
int		ut_slst_cat_interface(int N);
int		ut_slst_cat_memchk(int N);
int		ut_slst_cat_timeout(int N);
/***** slst_rev *****/
int		ut_slst_rev_interface(int N);
int		ut_slst_rev_memchk(int N);
int		ut_slst_rev_timeout(int N);
/***** slst_cut *****/
int		ut_slst_cut_interface(int N);
int		ut_slst_cut_memchk(int N);
int		ut_slst_cut_timeout(int N);
/***** slst_cutn *****/
int		ut_slst_cutn_interface(int N);
int		ut_slst_cutn_memchk(int N);
int		ut_slst_cutn_timeout(int N);
/***** slst_cutp *****/
int		ut_slst_cutp_interface(int N);
int		ut_slst_cutp_memchk(int N);
int		ut_slst_cutp_timeout(int N);
/***** slst_cutk *****/
int		ut_slst_cutk_interface(int N);
int		ut_slst_cutk_memchk(int N);
int		ut_slst_cutk_timeout(int N);
/***** slst_apply *****/
int		ut_slst_apply_interface(int N);
int		ut_slst_apply_memchk(int N);
int		ut_slst_apply_timeout(int N);
/***** slst_keyslen *****/
int		ut_slst_keyslen_interface(int N);
int		ut_slst_keyslen_memchk(int N);
int		ut_slst_keyslen_timeout(int N);
/***** slst_keysdup *****/
int		ut_slst_keysdup_interface(int N);
int		ut_slst_keysdup_memchk(int N);
int		ut_slst_keysdup_timeout(int N);

/***** slst_random *****/
int		ut_slst_random_interface(int N);
int		ut_slst_random_memchk(int N);
int		ut_slst_random_timeout(int N);
/***** slst2lifo *****/
int		ut_slst2lifo_interface(int N);
int		ut_slst2lifo_memchk(int N);
int		ut_slst2lifo_timeout(int N);
/***** slst2sclst *****/
int		ut_slst2sclst_interface(int N);
int		ut_slst2sclst_memchk(int N);
int		ut_slst2sclst_timeout(int N);
/***** slst2fifo *****/
int		ut_slst2fifo_interface(int N);
int		ut_slst2fifo_memchk(int N);
int		ut_slst2fifo_timeout(int N);
/***** slst_map *****/
int		ut_slst_map_interface(int N);
int		ut_slst_map_memchk(int N);
int		ut_slst_map_timeout(int N);

/***** mslst_purge *****/
int		ut_mslst_purge_interface(int N);
int		ut_mslst_purge_memchk(int N);
int		ut_mslst_purge_timeout(int N);


/*
** Structure LIFO (lifo_t)
*/
/***** lifo_purge *****/
int		ut_lifo_purge_interface(int N);
int		ut_lifo_purge_memchk(int N);
int		ut_lifo_purge_timeout(int N);
/***** lifo_push *****/
int		ut_lifo_push_interface(int N);
int		ut_lifo_push_memchk(int N);
int		ut_lifo_push_timeout(int N);
/***** lifo_pop *****/
int		ut_lifo_pop_interface(int N);
int		ut_lifo_pop_memchk(int N);
int		ut_lifo_pop_timeout(int N);
/***** lifo_map *****/
int		ut_lifo_map_interface(int N);
int		ut_lifo_map_memchk(int N);
int		ut_lifo_map_timeout(int N);

/*
** Mappage de structure LIFO (mlifo_t)
*/
/***** mlifo_push *****/
int		ut_mlifo_push_interface(int N);
int		ut_mlifo_push_memchk(int N);
int		ut_mlifo_push_timeout(int N);
/***** mlifo_pop *****/
int		ut_mlifo_pop_interface(int N);
int		ut_mlifo_pop_memchk(int N);
int		ut_mlifo_pop_timeout(int N);
/***** mlifo_purge *****/
int		ut_mlifo_purge_interface(int N);
int		ut_mlifo_purge_memchk(int N);
int		ut_mlifo_purge_timeout(int N);


/*
** Non-Ordered Simply Linked List (sclst_t)
*/
sclst_t	*_gen_sclst(size_t start, size_t end, size_t step);
/***** sclst_newelm *****/
int		ut_sclst_newelm_interface(int N);
int		ut_sclst_newelm_memchk(int N);
int		ut_sclst_newelm_timeout(int N);
/***** sclst_delelm *****/
int		ut_sclst_delelm_interface(int N);
int		ut_sclst_delelm_memchk(int N);
int		ut_sclst_delelm_timeout(int N);
/***** sclst_purge *****/
int		ut_sclst_purge_interface(int N);
int		ut_sclst_purge_memchk(int N);
int		ut_sclst_purge_timeout(int N);
/***** sclst_isempty *****/
int		ut_sclst_isempty_interface(int N);
int		ut_sclst_isempty_memchk(int N);
int		ut_sclst_isempty_timeout(int N);
/***** sclst_len *****/
int		ut_sclst_len_interface(int N);
int		ut_sclst_len_memchk(int N);
int		ut_sclst_len_timeout(int N);
/***** sclst_previous *****/
int		ut_sclst_previous_interface(int N);
int		ut_sclst_previous_memchk(int N);
int		ut_sclst_previous_timeout(int N);
/***** sclst_next *****/
int		ut_sclst_next_interface(int N);
int		ut_sclst_next_memchk(int N);
int		ut_sclst_next_timeout(int N);
/***** sclst_head *****/
int		ut_sclst_head_interface(int N);
int		ut_sclst_head_memchk(int N);
int		ut_sclst_head_timeout(int N);
/***** sclst_tail *****/
int		ut_sclst_tail_interface(int N);
int		ut_sclst_tail_memchk(int N);
int		ut_sclst_tail_timeout(int N);
/***** sclst_put *****/
int		ut_sclst_put_interface(int N);
int		ut_sclst_put_memchk(int N);
int		ut_sclst_put_timeout(int N);
/***** sclst_put_front *****/
int		ut_sclst_put_front_interface(int N);
int		ut_sclst_put_front_memchk(int N);
int		ut_sclst_put_front_timeout(int N);
/***** sclst_put_back *****/
int		ut_sclst_put_back_interface(int N);
int		ut_sclst_put_back_memchk(int N);
int		ut_sclst_put_back_timeout(int N);
/***** sclst_putn *****/
int		ut_sclst_putn_interface(int N);
int		ut_sclst_putn_memchk(int N);
int		ut_sclst_putn_timeout(int N);
/***** sclst_get *****/
int		ut_sclst_get_interface(int N);
int		ut_sclst_get_memchk(int N);
int		ut_sclst_get_timeout(int N);
/***** sclst_get_front *****/
int		ut_sclst_get_front_interface(int N);
int		ut_sclst_get_front_memchk(int N);
int		ut_sclst_get_front_timeout(int N);
/***** sclst_get_back *****/
int		ut_sclst_get_back_interface(int N);
int		ut_sclst_get_back_memchk(int N);
int		ut_sclst_get_back_timeout(int N);
/***** sclst_getn *****/
int		ut_sclst_getn_interface(int N);
int		ut_sclst_getn_memchk(int N);
int		ut_sclst_getn_timeout(int N);

/***** sclst_map *****/
int		ut_sclst_map_interface(int N);
int		ut_sclst_map_memchk(int N);
int		ut_sclst_map_timeout(int N);

/***** msclst_purge *****/
int		ut_msclst_purge_interface(int N);
int		ut_msclst_purge_memchk(int N);
int		ut_msclst_purge_timeout(int N);


/*
** Structure FIFO (fifo_t)
*/
/***** fifo_purge *****/
int		ut_fifo_purge_interface(int N);
int		ut_fifo_purge_memchk(int N);
int		ut_fifo_purge_timeout(int N);
/***** fifo_push *****/
int		ut_fifo_push_interface(int N);
int		ut_fifo_push_memchk(int N);
int		ut_fifo_push_timeout(int N);
/***** fifo_pop *****/
int		ut_fifo_pop_interface(int N);
int		ut_fifo_pop_memchk(int N);
int		ut_fifo_pop_timeout(int N);
/***** fifo_map *****/
int		ut_fifo_map_interface(int N);
int		ut_fifo_map_memchk(int N);
int		ut_fifo_map_timeout(int N);

/*
** Mappage de structure FIFO (mfifo_t)
*/
/***** mfifo_push *****/
int		ut_mfifo_push_interface(int N);
int		ut_mfifo_push_memchk(int N);
int		ut_mfifo_push_timeout(int N);
/***** mfifo_pop *****/
int		ut_mfifo_pop_interface(int N);
int		ut_mfifo_pop_memchk(int N);
int		ut_mfifo_pop_timeout(int N);
/***** mfifo_purge *****/
int		ut_mfifo_purge_interface(int N);
int		ut_mfifo_purge_memchk(int N);
int		ut_mfifo_purge_timeout(int N);

#endif
