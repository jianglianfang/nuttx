/****************************************************************************
 * libs/libc/spawn/lib_psa_destroy.c
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

#include <sched.h>
#include <spawn.h>
#include <assert.h>
#include <errno.h>

#include <nuttx/sched.h>

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: posix_spawnattr_destroy
 *
 * Description:
 *   The posix_spawnattr_destroy() function shall destroy a spawn attributes
 *   object. A destroyed attr attributes object can be reinitialized using
 *   posix_spawnattr_init();
 *
 * Input Parameters:
 *   attr - The address of the spawn attributes to be destroyed.
 *
 * Returned Value:
 *   Return 0 on success. On failure returns an error
 *   number from <errno.h>.
 *
 ****************************************************************************/

int posix_spawnattr_destroy(FAR posix_spawnattr_t *attr)
{
  UNUSED(attr);

  return OK;
}
