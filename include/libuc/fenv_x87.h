/*
** fenv_x87.h
**
** Header file for fenv_x87 subset of Undefined-C library
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

#ifndef FENV_X87_H
# define FENV_X87_H				1

# include <libuc/stdint.h>

# define FE_STATUS_IE			0x1				/* Invalid Exception */
# define FE_STATUS_DE			0x2				/* Denormalized Exception */
# define FE_STATUS_ZE			0x4				/* divide by Zero Exception */
# define FE_STATUS_OE			0x8				/* Overflow Exception */
# define FE_STATUS_UE			0x10			/* Underflow Exception */
# define FE_STATUS_PE			0x20			/* Inexact Exception */
# define FE_STATUS_SF			0x40			/* Stack Fault */
# define FE_STATUS_ES			0x80			/* Exception Summary */
# define FE_STATUS_C0			0x100			/* Condition flag 0 */
# define FE_STATUS_C1			0x200			/* Condition flag 1 */
# define FE_STATUS_C2			0x400			/* Condition flag 2 */
# define FE_STATUS_TOP			0x3800			/* Top of stack pointer */
# define FE_STATUS_C3			0x4000			/* Condition flag 3 */
# define FE_STATUS_B			0x8000			/* For 8087 compatibility, reflect FE_STATUS_ES */

# define FE_CONTROL_IM			0x1				/* Invalid exception Mask */
# define FE_CONTROL_DM			0x2				/* Denormalized exception Mask */
# define FE_CONTROL_ZM			0x4				/* dividde by Zero exception Mask */
# define FE_CONTROL_OM			0x8				/* Overflow exception Mask */
# define FE_CONTROL_UM			0x10			/* Underflow exception Mask */
# define FE_CONTROL_PM			0x20			/* Inexact exception Mask */
# define FE_CONTROL_RES0		0x40			/* Reserved, must be zero */
# define FE_CONTROL_RES1		0x80			/* Reserved, must be zero */
# define FE_CONTROL_PC			0x300			/* Precision Control */
# define FE_CONTROL_RC			0xc00			/* Rounding Control */
# define FE_CONTROL_X			0x1000			/* Infinity Control */
# define FE_CONTROL_RES2		0x2000			/* Reserved, must be zero */
# define FE_CONTROL_RES3		0x4000			/* Reserved, must be zero */
# define FE_CONTROL_RES4		0x8000			/* Reserved, must be zero */

# define FE_PRECISION_SGL		0x0				/* Single Precision (24 bits) 00b */
# define FE_PRECISION_RES0		0x1				/* Reserved 01b */
# define FE_PRECISION_DBL		0x2				/* Double Precision (53 bits) 10b */
# define FE_PRECISION_DBLEXT	0x3				/* Double Extended Precision (64 bits) 11b */

/*
** Standard C99/C11
*/
# define FE_TONEAREST			0x0
# define FE_DOWNWARD			0x400
# define FE_UPWARD				0x800
# define FE_TOWARDZERO			0xc00

# define FE_SETFLG(w,f)			w |= f
# define FE_CLEARFLG(w,f)		w &= (!f)

typedef struct					fenv_s
{
	uint16_t					__control_word;
	uint16_t					__res0;
	uint16_t					__status_word;
	uint16_t					__res1;
	uint16_t					__tag_word;
	uint16_t					__res2;
	uint32_t					__fip;
	uint16_t					__fcs;
	uint16_t					__opcode:11;
	uint16_t					__zeroed:5;
	uint32_t					__fdp;
	uint16_t					__fds;
	uint16_t					__res3;
# ifdef __x86_64__
	uint32_t					_mxcsr;
# endif
}								fenv_t;

#endif
