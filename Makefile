# $FreeBSD$

.PATH: ${.CURDIR}/../../fs/ntfs

KMOD=	ntfs
SRCS=	vnode_if.h \
	ntfs_appl.c \
	ntfs_attr.c \
	ntfs_attr.h \
	ntfs_attr_list.c \
	ntfs_bitmap.c \
	ntfs_collate.c \
	ntfs_compress.c \
	ntfs_debug.c \
	ntfs_dir.c \
	ntfs_index.c \
	ntfs_inode.c \
	ntfs_lcnalloc.c \
	ntfs_logfile.c \
	ntfs_mft.c \
	ntfs_mst.c \
	ntfs_page.c \
	ntfs_quota.c \
	ntfs_runlist.c \
	ntfs_secure.c \
	ntfs_sfm.c \
	ntfs_unistr.c \
	ntfs_usnjrnl.c \
	ntfs_vfsops.c \
	ntfs_vnops.c

.include <bsd.kmod.mk>
