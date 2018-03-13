;
; header.el
;
; header elisp script of Undefined-C library
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

; ***** Set command and hook *****
(global-set-key	(kbd "C-c C-h")	'header-insert)
(setq write-file-hooks (cons 'header-update write-file-hooks))

; ***** Set variable *****
(setq	developper_name		(getenv "DEVELOPPER_NAME")
		developper_mail		(getenv "DEVELOPPER_MAIL")
		license_line_0		"This file is a part free software; you can redistribute it and/or"
		license_line_1		"modify it under the terms of the GNU General Public License as"
		license_line_2		"published by the Free Software Foundation; either version 3, or"
		license_line_3		"(at your option) any later version."
		license_line_4		nil
		license_line_5		"There is distributed in the hope that it will be useful,"
		license_line_6		"but WITHOUT ANY WARRANTY; without even the implied warranty of"
		license_line_7		"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU"
		license_line_8		"General Public License for more details."
		license_line_9		nil
		license_line_10		"You should have received a copy of the GNU General Public License"
		license_line_11		"along with this program; see the file LICENSE.  If not, write to"
		license_line_12		"the Free Software Foundation, Inc., 51 Franklin Street, Fifth"
		license_line_13		"Floor, Boston, MA 02110-1301, USA.")

; ***** Declare function *****
(defun header-block-start ()
	"Make header block start string"
	(pcase (file-name-nondirectory buffer-file-name)
		("ltrace.conf"	";")
		(_				(pcase (file-name-extension buffer-file-name)
							("3"	".\\\"")
							(_		(if (string= (substring comment-start -1) comment-padding)
											(substring comment-start 0 -1)
										comment-start))))))

(defun header-block-newline ()
	"Make header block newline string"
	(pcase (file-name-nondirectory buffer-file-name)
		("ltrace.conf"	";")
		(_			    (pcase (file-name-extension buffer-file-name)
							("3"	".\\\"")
							(_		(if (> (length (header-block-start)) 1)
											(concat (substring (header-block-start) -1) (substring (header-block-start) -1))
										(header-block-start)))))))

(defun header-block-end ()
	"Make header block end string"
	(pcase (file-name-nondirectory buffer-file-name)
		("ltrace.conf"	";")
		(_			    (pcase (file-name-extension buffer-file-name)
							("3"	".\\\"")
							(_		(if (not (= (length comment-end) 0))
											(if (string= (substring comment-end 0 1) comment-padding)
													(substring comment-end 1)
												comment-end)
										(header-block-newline)))))))

(defun header-make-description-line ()
	"Make '<file_name> function for Undefined-C library' string."
	(pcase (file-name-nondirectory buffer-file-name)
		("Makefile"		"Make script of Undefined-C library")
		("ltrace.conf"	"ltrace configuration file of Undefined-C library")
		(_				(pcase (file-name-extension buffer-file-name)
							("h"	(concat "Header file for " (file-name-base buffer-file-name) " subset of Undefined-C library"))
							("c"	(pcase (substring (file-name-base buffer-file-name) 0 3)
										("ut_"	(concat "Unit tests for " (substring (file-name-base buffer-file-name) 3) " function of Undefined-C library"))
										(_ 		(concat (file-name-base buffer-file-name) " function of Undefined-C library"))))
							("cpp"	(concat (file-name-base buffer-file-name) " function of Undefined-C library"))
							("sh"	(concat (file-name-base buffer-file-name) " shell script of Undefined-C library"))
							("el"	(concat (file-name-base buffer-file-name) " elisp script of Undefined-C library"))
							("3"	(concat "Manpage for " (file-name-base buffer-file-name) " of Undefined-C library"))))))

(defun header-make-author-line (author_name author_mail)
	"Make 'By: <author_name> (<author_mail>)' string."
	(concat "By: " author_name " (" author_mail ")"))

(defun header-make-create-line (author_name)
	"Make 'Created: yyyy/mm/dd by <author_name>' string."
	(concat "Created: " (format-time-string "%Y/%m/%d") " by " author_name))

(defun header-make-update-line ()
	"Make 'Updated: yyyy/mm/dd by <developper_name>' string."
	(concat "Updated: " (format-time-string "%Y/%m/%d") " by " developper_name))

(defun header-insert-first-line ()
	"Insert first line of header in file"
	(insert (concat (header-block-start) "\n")))

(defun header-insert-line (&optional content)
	"Insert line of header in file"
	(if (not (null content))
			(insert (concat (header-block-newline) comment-padding content "\n"))
		(insert (concat (header-block-newline) "\n"))))

(defun header-insert-last-line ()
	"Insert last of header in file"
	(insert (concat (header-block-end) "\n")))

(defun header-update-line (content)
	"Update line of header in file"
	(insert (concat (header-block-newline) comment-padding content)))

(defun header-insert ()
	"Insert standard header in file"
	(interactive)
	(save-excursion
		(goto-char (point-min))
		(header-insert-first-line)
		(header-insert-line (file-name-nondirectory buffer-file-name))
		(header-insert-line)
		(header-insert-line (header-make-description-line))
		(header-insert-line)
		(header-insert-line (header-make-author-line developper_name developper_mail))
		(header-insert-line)
		(header-insert-line (header-make-create-line developper_name))
		(header-insert-line (header-make-update-line))
		(header-insert-line)
		(header-insert-line license_line_0)
		(header-insert-line license_line_1)
		(header-insert-line license_line_2)
		(header-insert-line license_line_3)
		(header-insert-line license_line_4)
		(header-insert-line license_line_5)
		(header-insert-line license_line_6)
		(header-insert-line license_line_7)
		(header-insert-line license_line_8)
		(header-insert-line license_line_9)
		(header-insert-line license_line_10)
		(header-insert-line license_line_11)
		(header-insert-line license_line_12)
		(header-insert-line license_line_13)
		(header-insert-last-line)))

(defun header-update ()
	"Update standard header in file"
	(interactive)
	(save-excursion
		(if (buffer-modified-p)
			(progn
				(goto-char (point-min))
				(if (search-forward "Updated" nil t)
					(progn
						(delete-region
							(progn (beginning-of-line) (point))
							(progn (end-of-line) (point)))
						(header-update-line (header-make-update-line))
						(message "Header up to date."))))))
	nil)

; *****  *****
(provide 'header)
