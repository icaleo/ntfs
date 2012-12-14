/*
 * ntfs_vnops.c - NTFS OS X kernel specific declaration.
 *
 * Copyright (c) 2006-2011 Anton Altaparmakov.  All Rights Reserved.
 * Portions Copyright (c) 2006-2011 Apple Inc.  All Rights Reserved.
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


typedef int errno_t;

typedef struct mount * mount_t;

typedef struct vnode * vnode_t;

typedef struct buf * buf_t;

typedef struct uio * uio_t;

typedef unsigned int     lck_rw_type_t;

#define LCK_RW_TYPE_SHARED                      0x01
#define LCK_RW_TYPE_EXCLUSIVE           0x02


/* return a pointer to the RO vfs_statfs associated with mount_t */
struct statfs * vfs_statfs(mount_t mp);

/* return a pointer to fs private data */
void * vfs_fsprivate(mount_t mp);

/* Vnode attributes check */
#define VATTR_IS_ACTIVE(v, a) ((v)->a != VNOVAL)

struct statfs * vfs_statfs(mount_t mp);
void * vfs_fsprivate(mount_t mp);
int vnode_isreg(vnode_t vp);
int vnode_ischr(vnode_t vp);
int vnode_isblk(vnode_t vp);
int vnode_issystem(vnode_t vp);
int vnode_isrecycled(vnode_t vp);
void *vnode_fsnode(vnode_t vp);
daddr64_t buf_lblkno(buf_t bp);
errno_t buf_map(buf_t bp, caddr_t *io_addr);
errno_t buf_unmap(buf_t bp);

