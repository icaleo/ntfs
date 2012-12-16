/*
 * ntfs_appl.c - NTFS OS X kernel specific function.
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

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/namei.h>
#include <sys/priv.h>
#include <sys/proc.h>
#include <sys/kernel.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/bio.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/endian.h>
#include <sys/fcntl.h>
#include <sys/malloc.h>
#include <sys/stat.h>
#include <sys/mutex.h>

#include <sys/lock.h>

#include "ntfs_appl.h"
#include "ntfs_types.h"
#include "ntfs_endian.h"

/* return a pointer to the RO vfs_statfs associated with mount_t */
struct statfs * vfs_statfs(mount_t mp)
{
        return(&mp->mnt_stat);
}

/* return a pointer to fs private data */
void * vfs_fsprivate(mount_t mp)
{
        return(mp->mnt_data);
}

/* is vnode_t a regular file */
int vnode_isreg(vnode_t vp)
{
        return ((vp->v_type == VREG)? 1 : 0);
}

/* is vnode_t a char device? */
int vnode_ischr(vnode_t vp)
{
        return ((vp->v_type == VCHR)? 1 : 0);
}

/* is vnode_t a block device? */
int vnode_isblk(vnode_t vp)
{
        return ((vp->v_type == VBLK)? 1 : 0);
}

/* is vnode_t a system vnode */
int vnode_issystem(vnode_t vp)
{
        return ((vp->v_vflag & VV_SYSTEM)? 1 : 0);
}

/* is this vnode under recyle now */
int vnode_isrecycled(vnode_t vp)
{
        int ret;

        VI_LOCK(vp);
        ret =  (vp->v_iflag & VI_DOOMED)? 1 : 0;
        VI_UNLOCK(vp);
        return(ret);
}

/* returns FS specific node saved in vnode */
void *vnode_fsnode(vnode_t vp)
{
	return (vp->v_data);
}

uint32_t buf_flags(buf_t bp) 
{
        return ((bp->b_flags));
}

daddr64_t buf_lblkno(buf_t bp)
{
        return (bp->b_lblkno);
}

errno_t buf_map(buf_t bp, caddr_t *io_addr)
{
	*io_addr = (caddr_t)bp->b_data;
	return (0);
}

errno_t buf_unmap(buf_t bp)
{
	return (0);
}
