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

	.macro	mediatek_disable_interrupts
	.set	push
	.set	noreorder
	mfc0	k0, CP0_STATUS
	li	k1, ~(ST0_IE)
	and	k0, k1
	mtc0	k0, CP0_STATUS
	.set	pop
	.endm
