﻿/*
	Copyright(C) 2007-2016, ManTechnology Co., LTD.
	Copyright(C) 2007-2016, wdrbd@mantech.co.kr

	Windows DRBD is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2, or (at your option)
	any later version.

	Windows DRBD is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Windows DRBD; see the file COPYING. If not, write to
	the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include <ntddk.h>
#include "disp.h"
#include "proto.h"
#include "drbd_int.h"
#include "drbd_polymorph_printk.h"

PDEVICE_OBJECT	mvolRootDeviceObject;
PDRIVER_OBJECT	mvolDriverObject;
KSPIN_LOCK		mvolVolumeLock;
KMUTEX			mvolMutex;
KMUTEX			eventlogMutex;
PETHREAD		g_NetlinkServerThread;

int				seq_file_idx		= 0;

EX_SPIN_LOCK g_rcuLock;
struct ratelimit_state drbd_ratelimit_state;

struct mutex notification_mutex;
struct mutex g_genl_mutex;
KSPIN_LOCK	transport_classes_lock;


/* https://vxlab.info/wasm/print.php-article=npi_subvert.htm */
const NPIID NPI_WSK_INTERFACE_ID = {
	0x2227E803, 0x8D8B, 0x11D4,
	{0xAB, 0xAD, 0x00, 0x90, 0x27, 0x71, 0x9E, 0x09}
};
