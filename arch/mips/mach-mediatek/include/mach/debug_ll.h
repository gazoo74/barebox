// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2017 Gaël PORTAY <gael.portay@savoirfairelinux.com>
 */

/** @file
 *  This File contains declaration for early output support
 */
#ifndef __MEDIATEK_DEBUG_LL_H__
#define __MEDIATEK_DEBUG_LL_H__

#define MT7628_UARTLITE_CLK	40000000
#define MT7628_UARTLITE1_BASE	0x10000c00
#define MT7628_UARTLITE2_BASE	0x10000d00
#define MT7628_UARTLITE3_BASE	0x10000e00

#ifdef CONFIG_DEBUG_MT7628_UARTLITE0
#define DEBUG_LL_UART_ADDR	MT7628_UARTLITE1_BASE
#else
#ifdef CONFIG_DEBUG_MT7628_UARTLITE1
#define DEBUG_LL_UART_ADDR	MT7628_UARTLITE2_BASE
#else
#define DEBUG_LL_UART_ADDR	MT7628_UARTLITE3_BASE
#endif
#endif

#define DEBUG_LL_UART_SHIFT	2
#define DEBUG_LL_UART_DIVISOR   (MT7628_UARTLITE_CLK / 16 / CONFIG_BAUDRATE)

#include <asm/debug_ll_ns16550.h>

#endif /* __MEDIATEK_DEBUG_LL_H__ */
