/* Tracker - indexer and metadata database engine
 * Copyright (C) 2006, Mr Jamie McCracken (jamiemcc@gnome.org)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */
 
#include "config.h"

#ifdef IOPRIO_SUPPORT

#include <stdio.h>
#include <errno.h>
#include <glib/gstdio.h>
#include <tracker-utils.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "tracker-ioprio.h"

enum {
	IOPRIO_CLASS_NONE,
	IOPRIO_CLASS_RT,
	IOPRIO_CLASS_BE,
	IOPRIO_CLASS_IDLE,
};

enum {
	IOPRIO_WHO_PROCESS = 1,
	IOPRIO_WHO_PGRP,
	IOPRIO_WHO_USER,
};

#define IOPRIO_CLASS_SHIFT	13

static inline int ioprio_set (int which, int who, int ioprio)
{
	return syscall (__NR_ioprio_set, which, who, ioprio);
}

static inline int ioprio_get (int which, int who)
{
	return syscall (__NR_ioprio_get, which, who);
}

void ioprio()
{
	int ioprio = 7, ioprio_class = IOPRIO_CLASS_BE;
	tracker_log ("Setting ioprio best effort.");
	
	if (ioprio_set(IOPRIO_WHO_PROCESS,0,ioprio | ioprio_class << IOPRIO_CLASS_SHIFT) == -1) {
		perror ("ioprio_set returns error.");
	}
}

#endif
