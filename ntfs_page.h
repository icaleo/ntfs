/*
 * ntfs_page.h - Defines for page handling in the NTFS kernel driver.
 *
 * Copyright (c) 2006-2008 Anton Altaparmakov.  All Rights Reserved.
 * Portions Copyright (c) 2006-2008 Apple Inc.  All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution. 
 * 3. Neither the name of Apple Inc. ("Apple") nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ALTERNATIVELY, provided that this notice and licensing terms are retained in
 * full, this file may be redistributed and/or modified under the terms of the
 * GNU General Public License (GPL) Version 2, in which case the provisions of
 * that version of the GPL will apply to you instead of the license terms
 * above.  You can obtain a copy of the GPL Version 2 at
 * http://developer.apple.com/opensource/licenses/gpl-2.txt.
 */

#ifndef _BSD_NTFS_PAGE_H
#define _BSD_NTFS_PAGE_H


#include "ntfs_inode.h"
#include "ntfs_types.h"

extern errno_t ntfs_page_map_ext(ntfs_inode *ni, s64 ofs, buf_t *bpp, 
		caddr_t *io_addr, const BOOL uptodate, const BOOL rw);

/**
 * ntfs_page_map - map a page of a vnode into memory
 * @ni:		ntfs inode of which to map a page
 * @ofs:	byte offset into @ni of which to map a page
 * @bpp         buf_t pointer
 * @io_addr     bp->b_data addr for io
 * @rw:		if true we intend to modify the page and if false we do not
 *
 * Map the page corresponding to byte offset @ofs into the ntfs inode @ni into
 * memory and return the page list in @upl, the array of pages containing the
 * page in @pl and the address of the mapped page contents in @kaddr.
 *
 * The page is returned uptodate.
 *
 * The caller must set @rw to true if the page is going to be modified and to
 * false otherwise.
 *
 * Note: @ofs must be page aligned.
 *
 * Locking: - Caller must hold an iocount reference on the vnode of @ni.
 *	    - Caller must hold @ni->lock for reading or writing.
 */
static inline errno_t ntfs_page_map(ntfs_inode *ni, s64 ofs, buf_t *bpp,
		caddr_t *io_addr, const BOOL rw)
{
	return ntfs_page_map_ext(ni, ofs, bpp, io_addr, TRUE, rw);
}

/**
 * ntfs_page_grab - map a page of a vnode into memory
 * @ni:		ntfs inode of which to map a page
 * @ofs:	byte offset into @ni of which to map a page
 * @bpp         buf_t pointer
 * @io_addr     bp->b_data addr for io
 * @rw:		if true we intend to modify the page and if false we do not
 *
 * Map the page corresponding to byte offset @ofs into the ntfs inode @ni into
 * memory and return the page list in @upl, the array of pages containing the
 * page in @pl and the address of the mapped page contents in @kaddr.
 *
 * The page is returned in whatever state it is obtained from the VM, i.e. it
 * may or may not be uptodate.
 *
 * The caller must set @rw to true if the page is going to be modified and to
 * false otherwise.
 *
 * Note: @ofs must be page aligned.
 *
 * Locking: - Caller must hold an iocount reference on the vnode of @ni.
 *	    - Caller must hold @ni->lock for reading or writing.
 */
static inline errno_t ntfs_page_grab(ntfs_inode *ni, s64 ofs, buf_t *bpp,
		caddr_t *io_addr, u8 **kaddr, const BOOL rw)
{
	return ntfs_page_map_ext(ni, ofs, bpp, io_addr, FALSE, rw);
}

extern void ntfs_page_unmap(ntfs_inode *ni, buf_t bp, const BOOL mark_dirty);

extern void ntfs_page_dump(ntfs_inode *ni, buf_t bp);

#endif /* !_BSD_NTFS_PAGE_H */
