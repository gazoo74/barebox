// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2017 Gaël PORTAY <gael.portay@savoirfairelinux.com>
 */

#define BOARD_PBL_START start_vonger_vocore2

#include <asm/asm.h>
#include <asm/pbl_macros.h>
#include <asm/pbl_nmon.h>
#include <mach/pbl_macros.h>

ENTRY_FUNCTION(BOARD_PBL_START)

	mips_barebox_10h

	pbl_blt 0xbf000000 skip_config t8

	mediatek_disable_interrupts

skip_config:

ENTRY_FUNCTION_END(BOARD_PBL_START, vonger_vocore2)
