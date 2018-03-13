;
; emacs.el
;
; emacs elisp script of Undefined-C library
;
; By: Juillard Jean-Baptiste (jbjuillard@gmail.com)
;
; Created: 2018/03/10 by Juillard Jean-Baptiste
; Updated: 2018/03/12 by Juillard Jean-Baptiste
;
; This file is a part free software; you can redistribute it and/or
; modify it under the terms of the GNU General Public License as
; published by the Free Software Foundation; either version 3, or
; (at your option) any later version.
;
; There is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
; General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program; see the file LICENSE.  If not, write to
; the Free Software Foundation, Inc., 51 Franklin Street, Fifth
; Floor, Boston, MA 02110-1301, USA.
;

; Load dependencies
(load "header.el")

; Set default Emacs configuration for libuc project
(set-language-environment "UTF-8")
(setq-default	tab-width			4
				line-number-mode	t
				column-number-mode	t
				c-basic-offset		4)

; Load user configuration
(if (file-exists-p "myemacs.el") (load "myemacs.el"))
