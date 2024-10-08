/****************************************************************************
 * libs/libc/stdio/lib_libflushall.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>

#include <nuttx/nuttx.h>
#include <nuttx/fs/fs.h>

#include "libc.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: lib_flushall
 *
 * Description:
 *   Called either (1) by the OS when a task exits, or (2) from fflush()
 *   when a NULL stream argument is provided.
 *
 ****************************************************************************/

int lib_flushall_unlocked(FAR struct streamlist *list)
{
  FAR sq_entry_t *entry;
  int lasterrno = OK;
  int ret;

  /* Make sure that there are streams associated with this thread */

  if (list != NULL)
    {
      FAR FILE *stream;
      int i;

      /* Process each stream in the thread's stream list */

      for (i = 0; i < 3; i++)
        {
          lib_fflush_unlocked(&list->sl_std[i]);
        }

      sq_for_every(&list->sl_queue, entry)
        {
          stream = container_of(entry, struct file_struct, fs_entry);

          /* If the stream is opened for writing, then flush all of
           * the pending write data in the stream.
           */

          if ((stream->fs_oflags & O_WROK) != 0)
            {
              /* Flush the writable FILE */

              ret = lib_fflush_unlocked(stream);
              if (ret < 0)
                {
                  /* An error occurred during the flush AND/OR we were unable
                   * to flush all of the buffered write data.  Remember the
                   * last errcode.
                   */

                  lasterrno = ret;
                }
            }
        }
    }

  /* If any flush failed, return the errorcode of the last failed flush */

  return lasterrno;
}

int lib_flushall(FAR struct streamlist *list)
{
  FAR sq_entry_t *entry;
  int lasterrno = OK;
  int ret;

  /* Make sure that there are streams associated with this thread */

  if (list != NULL)
    {
      FAR FILE *stream;
      int i;

      /* Process each stream in the thread's stream list */

      nxmutex_lock(&list->sl_lock);

      for (i = 0; i < 3; i++)
        {
          lib_fflush(&list->sl_std[i]);
        }

      sq_for_every(&list->sl_queue, entry)
        {
          stream = container_of(entry, struct file_struct, fs_entry);

          /* If the stream is opened for writing, then flush all of
           * the pending write data in the stream.
           */

          if ((stream->fs_oflags & O_WROK) != 0)
            {
              /* Flush the writable FILE */

              ret = lib_fflush(stream);
              if (ret < 0)
                {
                  /* An error occurred during the flush AND/OR we were unable
                   * to flush all of the buffered write data.  Remember the
                   * last errcode.
                   */

                  lasterrno = ret;
                }
            }
        }

      nxmutex_unlock(&list->sl_lock);
    }

  /* If any flush failed, return the errorcode of the last failed flush */

  return lasterrno;
}
