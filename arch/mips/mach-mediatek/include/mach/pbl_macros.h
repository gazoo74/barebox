// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2017 Gaël PORTAY <gael.portay@savoirfairelinux.com>
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
