/* SPDX-License-Identifier: LGPL-2.1+ */
/***
  This file is part of systemd.

  Copyright 2010 Lennart Poettering
  Copyright 2010 Harald Hoyer

  systemd is free software; you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.

  systemd is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with systemd; If not, see <http://www.gnu.org/licenses/>.
***/

#include <sys/stat.h>

#include "fileio-label.h"
//#include "fileio.h"
#include "selinux-util.h"

int write_string_file_atomic_label_ts(const char *fn, const char *line, struct timespec *ts) {
        int r;

        r = mac_selinux_create_file_prepare(fn, S_IFREG);
        if (r < 0)
                return r;

        r = write_string_file_ts(fn, line, WRITE_STRING_FILE_CREATE|WRITE_STRING_FILE_ATOMIC, ts);

        mac_selinux_create_file_clear();

        return r;
}

#if 0 /// UNNEEDED by elogind
int write_env_file_label(const char *fname, char **l) {
        int r;

        r = mac_selinux_create_file_prepare(fname, S_IFREG);
        if (r < 0)
                return r;

        r = write_env_file(fname, l);

        mac_selinux_create_file_clear();

        return r;
}

int fopen_temporary_label(const char *target,
                          const char *path, FILE **f, char **temp_path) {
        int r;

        r = mac_selinux_create_file_prepare(target, S_IFREG);
        if (r < 0)
                return r;

        r = fopen_temporary(path, f, temp_path);

        mac_selinux_create_file_clear();

        return r;
}
#endif // 0

int create_shutdown_run_nologin_or_warn(void) {
        int r;

        /* This is used twice: once in systemd-user-sessions.service, in order to block logins when we actually go
         * down, and once in systemd-logind.service when shutdowns are scheduled, and logins are to be turned off a bit
         * in advance. We use the same wording of the message in both cases. */

        r = write_string_file_atomic_label("/run/nologin",
                                           "System is going down. Unprivileged users are not permitted to log in anymore. "
                                           "For technical details, see pam_nologin(8).");
        if (r < 0)
                return log_error_errno(r, "Failed to create /run/nologin: %m");

        return 0;
}
