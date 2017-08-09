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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

/** @file
 *  This File contains declaration for early output support
 */
#ifndef __VOCORE2_DEBUG_LL_H__
#define __VOCORE2_DEBUG_LL_H__

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

#endif /* __VOCORE2_DEBUG_LL_H__ */
