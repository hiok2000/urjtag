#
# $Id$
#
# Copyright (C) 2003 ETC s.r.o.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.
#
# Written by Marcel Telka <marcel@telka.sk>, 2003.
#

include $(top_srcdir)/Makefile.rules

noinst_LTLIBRARIES = libcmd.la

always_enabled_cmd_files = \
		$(top_srcdir)/src/cmd/cmd_frequency.c \
		$(top_srcdir)/src/cmd/cmd_cable.c \
		$(top_srcdir)/src/cmd/cmd_reset.c \
		$(top_srcdir)/src/cmd/cmd_discovery.c \
		$(top_srcdir)/src/cmd/cmd_idcode.c \
		$(top_srcdir)/src/cmd/cmd_detect.c \
		$(top_srcdir)/src/cmd/cmd_detectflash.c \
		$(top_srcdir)/src/cmd/cmd_help.c \
		$(top_srcdir)/src/cmd/cmd_quit.c \
		$(top_srcdir)/src/cmd/cmd_scan.c \
		$(top_srcdir)/src/cmd/cmd_signal.c \
		$(top_srcdir)/src/cmd/cmd_salias.c \
		$(top_srcdir)/src/cmd/cmd_bit.c \
		$(top_srcdir)/src/cmd/cmd_register.c \
		$(top_srcdir)/src/cmd/cmd_initbus.c \
		$(top_srcdir)/src/cmd/cmd_print.c \
		$(top_srcdir)/src/cmd/cmd_part.c \
		$(top_srcdir)/src/cmd/cmd_bus.c \
		$(top_srcdir)/src/cmd/cmd_instruction.c \
		$(top_srcdir)/src/cmd/cmd_shift.c \
		$(top_srcdir)/src/cmd/cmd_dr.c \
		$(top_srcdir)/src/cmd/cmd_get.c \
		$(top_srcdir)/src/cmd/cmd_test.c \
		$(top_srcdir)/src/cmd/cmd_debug.c \
		$(top_srcdir)/src/cmd/cmd_shell.c \
		$(top_srcdir)/src/cmd/cmd_set.c \
		$(top_srcdir)/src/cmd/cmd_endian.c \
		$(top_srcdir)/src/cmd/cmd_peekpoke.c \
		$(top_srcdir)/src/cmd/cmd_pod.c \
		$(top_srcdir)/src/cmd/cmd_readmem.c \
		$(top_srcdir)/src/cmd/cmd_writemem.c \
		$(top_srcdir)/src/cmd/cmd_flashmem.c \
		$(top_srcdir)/src/cmd/cmd_eraseflash.c \
		$(top_srcdir)/src/cmd/cmd_lockflash.c \
		$(top_srcdir)/src/cmd/cmd_include.c \
		$(top_srcdir)/src/cmd/cmd_addpart.c \
		$(top_srcdir)/src/cmd/cmd_cmd.c \
		$(top_srcdir)/src/cmd/cmd_usleep.c \
		$(top_srcdir)/src/cmd/cmd_bfin.c \
		$(top_srcdir)/src/cmd/cmd_pld.c

libcmd_la_SOURCES = \
	cmd.h \
	cmd_list.h \
	generated_cmd_list.h \
	$(always_enabled_cmd_files)

if ENABLE_SVF
libcmd_la_SOURCES += cmd_svf.c
endif

if ENABLE_BSDL
libcmd_la_SOURCES += cmd_bsdl.c
endif

if ENABLE_STAPL
libcmd_la_SOURCES += cmd_stapl.c
endif

# This list has to be unconditional so the generated header always contains
# all possible commands.  We control which ones actually get enabled via
# defines from config.h.
all_cmd_files = \
	$(always_enabled_cmd_files) \
	$(top_srcdir)/src/cmd/cmd_bsdl.c \
	$(top_srcdir)/src/cmd/cmd_stapl.c \
	$(top_srcdir)/src/cmd/cmd_svf.c

generated_cmd_list.h: generated_cmd_list.h.stamp ; @true
generated_cmd_list.h.stamp: $(all_cmd_files)
	$(AM_V_GEN)set -e; \
	cmds=`$(SED) -n '/^const urj_cmd_t urj_cmd_/{s:.*urj_cmd_::;s: =.*::;p;}' $(all_cmd_files)`; \
	for c in $$cmds ; do \
		printf '#ifndef URJ_CMD_SKIP_%s\n_URJ_CMD(%s)\n#endif\n' $$c $$c; \
	done > generated_cmd_list.h.tmp; \
	if cmp -s generated_cmd_list.h generated_cmd_list.h.tmp; then \
		echo generated_cmd_list.h is unchanged; \
		rm -f generated_cmd_list.h.tmp; \
	else \
		echo updating generated_cmd_list.h; \
		mv generated_cmd_list.h.tmp generated_cmd_list.h; \
	fi; \
	touch $@

BUILT_SOURCES = generated_cmd_list.h
EXTRA_DIST = generated_cmd_list.h generated_cmd_list.h.stamp
MAINTAINERCLEANFILES = generated_cmd_list.h generated_cmd_list.h.stamp

AM_CFLAGS = $(WARNINGCFLAGS)
