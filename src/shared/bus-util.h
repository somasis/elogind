/* SPDX-License-Identifier: LGPL-2.1+ */
#pragma once

/***
  This file is part of systemd.

  Copyright 2013 Lennart Poettering

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

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#include "sd-bus.h"
#include "sd-event.h"

#include "hashmap.h"
#include "macro.h"
#include "string-util.h"

typedef enum BusTransport {
        BUS_TRANSPORT_LOCAL,
        BUS_TRANSPORT_REMOTE,
        BUS_TRANSPORT_MACHINE,
        _BUS_TRANSPORT_MAX,
        _BUS_TRANSPORT_INVALID = -1
} BusTransport;

typedef int (*bus_property_set_t) (sd_bus *bus, const char *member, sd_bus_message *m, sd_bus_error *error, void *userdata);

struct bus_properties_map {
        const char *member;
        const char *signature;
        bus_property_set_t set;
        size_t offset;
};

int bus_map_id128(sd_bus *bus, const char *member, sd_bus_message *m, sd_bus_error *error, void *userdata);

int bus_message_map_all_properties(sd_bus_message *m, const struct bus_properties_map *map, sd_bus_error *error, void *userdata);
#if 0 /// UNNEEDED by elogind
int bus_message_map_properties_changed(sd_bus_message *m, const struct bus_properties_map *map, sd_bus_error *error, void *userdata);
#endif // 0
int bus_map_all_properties(sd_bus *bus, const char *destination, const char *path, const struct bus_properties_map *map, sd_bus_error *error, void *userdata);

#if 0 /// UNNEEDED by elogind
int bus_async_unregister_and_exit(sd_event *e, sd_bus *bus, const char *name);
#endif // 0

typedef bool (*check_idle_t)(void *userdata);

#if 0 /// UNNEEDED by elogind
int bus_event_loop_with_idle(sd_event *e, sd_bus *bus, const char *name, usec_t timeout, check_idle_t check_idle, void *userdata);
#endif // 0

int bus_name_has_owner(sd_bus *c, const char *name, sd_bus_error *error);

#if 0 /// UNNEEDED by elogind
int bus_check_peercred(sd_bus *c);
#endif // 0

int bus_test_polkit(sd_bus_message *call, int capability, const char *action, const char **details, uid_t good_user, bool *_challenge, sd_bus_error *e);

int bus_verify_polkit_async(sd_bus_message *call, int capability, const char *action, const char **details, bool interactive, uid_t good_user, Hashmap **registry, sd_bus_error *error);
void bus_verify_polkit_async_registry_free(Hashmap *registry);

#if 0 /// UNNEEDED by elogind
#endif // 0
int bus_connect_system_systemd(sd_bus **_bus);
int bus_connect_user_systemd(sd_bus **_bus);

int bus_connect_transport(BusTransport transport, const char *host, bool user, sd_bus **bus);
#if 0 /// UNNEEDED by elogind
#endif // 0
int bus_connect_transport_systemd(BusTransport transport, const char *host, bool user, sd_bus **bus);

int bus_print_property(const char *name, sd_bus_message *property, bool value, bool all);
int bus_print_all_properties(sd_bus *bus, const char *dest, const char *path, char **filter, bool value, bool all);

int bus_property_get_bool(sd_bus *bus, const char *path, const char *interface, const char *property, sd_bus_message *reply, void *userdata, sd_bus_error *error);
int bus_property_set_bool(sd_bus *bus, const char *path, const char *interface, const char *property, sd_bus_message *value, void *userdata, sd_bus_error *error);
#if 0 /// UNNEEDED by elogind
int bus_property_get_id128(sd_bus *bus, const char *path, const char *interface, const char *property, sd_bus_message *reply, void *userdata, sd_bus_error *error);
#endif // 0

#define bus_property_get_usec ((sd_bus_property_get_t) NULL)
#define bus_property_set_usec ((sd_bus_property_set_t) NULL)

assert_cc(sizeof(int) == sizeof(int32_t));
#define bus_property_get_int ((sd_bus_property_get_t) NULL)

assert_cc(sizeof(unsigned) == sizeof(unsigned));
#define bus_property_get_unsigned ((sd_bus_property_get_t) NULL)

/* On 64bit machines we can use the default serializer for size_t and
 * friends, otherwise we need to cast this manually */
#if __SIZEOF_SIZE_T__ == 8
#define bus_property_get_size ((sd_bus_property_get_t) NULL)
#else
int bus_property_get_size(sd_bus *bus, const char *path, const char *interface, const char *property, sd_bus_message *reply, void *userdata, sd_bus_error *error);
#endif

#if __SIZEOF_LONG__ == 8
#define bus_property_get_long ((sd_bus_property_get_t) NULL)
#define bus_property_get_ulong ((sd_bus_property_get_t) NULL)
#else
int bus_property_get_long(sd_bus *bus, const char *path, const char *interface, const char *property, sd_bus_message *reply, void *userdata, sd_bus_error *error);
int bus_property_get_ulong(sd_bus *bus, const char *path, const char *interface, const char *property, sd_bus_message *reply, void *userdata, sd_bus_error *error);
#endif

/* uid_t and friends on Linux 32 bit. This means we can just use the
 * default serializer for 32bit unsigned, for serializing it, and map
 * it to NULL here */
assert_cc(sizeof(uid_t) == sizeof(uint32_t));
#define bus_property_get_uid ((sd_bus_property_get_t) NULL)

assert_cc(sizeof(gid_t) == sizeof(uint32_t));
#define bus_property_get_gid ((sd_bus_property_get_t) NULL)

assert_cc(sizeof(pid_t) == sizeof(uint32_t));
#define bus_property_get_pid ((sd_bus_property_get_t) NULL)

assert_cc(sizeof(mode_t) == sizeof(uint32_t));
#define bus_property_get_mode ((sd_bus_property_get_t) NULL)

int bus_log_parse_error(int r);
int bus_log_create_error(int r);

#if 0 /// UNNEEDED by elogind
#endif // 0
#define BUS_DEFINE_PROPERTY_GET_ENUM(function, name, type)              \
        int function(sd_bus *bus,                                       \
                     const char *path,                                  \
                     const char *interface,                             \
                     const char *property,                              \
                     sd_bus_message *reply,                             \
                     void *userdata,                                    \
                     sd_bus_error *error) {                             \
                                                                        \
                const char *value;                                      \
                type *field = userdata;                                 \
                int r;                                                  \
                                                                        \
                assert(bus);                                            \
                assert(reply);                                          \
                assert(field);                                          \
                                                                        \
                value = strempty(name##_to_string(*field));             \
                                                                        \
                r = sd_bus_message_append_basic(reply, 's', value);     \
                if (r < 0)                                              \
                        return r;                                       \
                                                                        \
                return 1;                                               \
        }                                                               \
        struct __useless_struct_to_allow_trailing_semicolon__

#define BUS_PROPERTY_DUAL_TIMESTAMP(name, offset, flags) \
        SD_BUS_PROPERTY(name, "t", bus_property_get_usec, (offset) + offsetof(struct dual_timestamp, realtime), (flags)), \
        SD_BUS_PROPERTY(name "Monotonic", "t", bus_property_get_usec, (offset) + offsetof(struct dual_timestamp, monotonic), (flags))

#if 0 /// UNNEEDED by elogind
int bus_path_encode_unique(sd_bus *b, const char *prefix, const char *sender_id, const char *external_id, char **ret_path);
int bus_path_decode_unique(const char *path, const char *prefix, char **ret_sender, char **ret_external);
#endif // 0

#if 0 /// UNNEEDED by elogind
int bus_property_get_rlimit(sd_bus *bus, const char *path, const char *interface, const char *property, sd_bus_message *reply, void *userdata, sd_bus_error *error);

int bus_track_add_name_many(sd_bus_track *t, char **l);
#endif // 0

int bus_open_system_watch_bind(sd_bus **ret);
