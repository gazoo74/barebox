/*
 * Copyright (C) 2017 Gaël PORTAY <gael.portay@savoirfairelinux.com>
 *
 * This file is part of barebox.
 * See file CREDITS for list of people who contributed to this project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 */

#include <asm/pbl_macros.h>
#include <mach/pbl_macros.h>
#include <mach/debug_ll.h>

	.macro	board_pbl_start
	.set	push
	.set	noreorder

	mips_barebox_10h

	pbl_blt 0xbf000000 skip_config t8

	mediatek_disable_interrupts

skip_config:

	copy_to_link_location	pbl_start

	.set	pop
	.endm
