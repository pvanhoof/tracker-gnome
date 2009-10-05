/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * Copyright (C) 2009, Nokia (urho.konttori@nokia.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

#ifndef __LIBTRACKERMINER_MINER_FS_H__
#define __LIBTRACKERMINER_MINER_FS_H__

#include <glib-object.h>
#include <gio/gio.h>

#include <libtracker-common/tracker-sparql-builder.h>

#include "tracker-miner.h"

G_BEGIN_DECLS

#define TRACKER_TYPE_MINER_FS         (tracker_miner_fs_get_type())
#define TRACKER_MINER_FS(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), TRACKER_TYPE_MINER_FS, TrackerMinerFS))
#define TRACKER_MINER_FS_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), TRACKER_TYPE_MINER_FS, TrackerMinerFSClass))
#define TRACKER_IS_MINER_FS(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), TRACKER_TYPE_MINER_FS))
#define TRACKER_IS_MINER_FS_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c),  TRACKER_TYPE_MINER_FS))
#define TRACKER_MINER_FS_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TRACKER_TYPE_MINER_FS, TrackerMinerFSClass))

typedef struct TrackerMinerFS        TrackerMinerFS;
typedef struct TrackerMinerFSPrivate TrackerMinerFSPrivate;

/**
 * TrackerMinerFSDoneCb:
 * @fs: The #TrackerMinerFS
 * @file: The #GFile corresponding to the asynchronous call
 * @builder: a #TrackerSparqlBuilder to collect data
 * @error: #GError with the extraction error, or %NULL if none
 * @user_data: passed user data to the asynchronous call
 *
 * This callback is passed for each inspected #GFile in the
 * TrackerMinerFS::process_file() vmethod, it's the implementation
 * responsibility to call it as soon as all metadata extraction has
 * been performed on @file.
 **/
typedef void (* TrackerMinerFSDoneCb) (TrackerMinerFS       *fs,
				       GFile                *file,
				       TrackerSparqlBuilder *builder,
				       const GError         *error,
				       gpointer              user_data);

struct TrackerMinerFS {
	TrackerMiner parent;
	TrackerMinerFSPrivate *private;
};

/**
 * TrackerMinerFSClass:
 * @parent: parent object class
 * @check_file: Called when a file should be checked for further processing
 * @check_directory: Called when a directory should be checked for further processing
 * @check_directory_contents: Called when a directory should be checked for further processing, based on the directory contents.
 * @process_file: Called when the metadata associated to a file is requested.
 * @monitor_directory: Called to check whether a directory should be modified.
 * @finished: Called when all processing has been performed.
 *
 * Prototype for the abstract class, @check_file, @check_directory, @check_directory_contents,
 * @process_file and @monitor_directory must be implemented in the deriving class in order to
 * actually extract data.
 **/
typedef struct {
	TrackerMinerClass parent;

	gboolean (* check_file)            (TrackerMinerFS       *fs,
					    GFile                *file);
	gboolean (* check_directory)       (TrackerMinerFS       *fs,
					    GFile                *file);
	gboolean (* check_directory_contents) (TrackerMinerFS    *fs,
					       GFile             *parent,
					       GList             *children);
	gboolean (* process_file)          (TrackerMinerFS       *fs,
					    GFile                *file,
					    TrackerSparqlBuilder *builder,
					    GCancellable         *cancellable,
					    TrackerMinerFSDoneCb  done_cb,
					    gpointer              done_cb_data);
	gboolean (* monitor_directory)     (TrackerMinerFS       *fs,
					    GFile                *file);
	void     (* finished)              (TrackerMinerFS       *fs);
} TrackerMinerFSClass;

GType    tracker_miner_fs_get_type         (void) G_GNUC_CONST;

void     tracker_miner_fs_add_directory    (TrackerMinerFS *fs,
					    GFile          *file,
					    gboolean        recurse);
gboolean tracker_miner_fs_remove_directory (TrackerMinerFS *fs,
					    GFile          *file);

void     tracker_miner_fs_set_throttle     (TrackerMinerFS *fs,
					    gdouble         throttle);
gdouble  tracker_miner_fs_get_throttle     (TrackerMinerFS *fs);

G_END_DECLS

#endif /* __LIBTRACKERMINER_MINER_FS_H__ */
