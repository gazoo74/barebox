# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2017 Gaël PORTAY <gael.portay@savoirfairelinux.com>
#

ARCH = mips
CROSS_COMPILE = mipsel-unknown-linux-gnu-

export ARCH CROSS_COMPILE

.PHONY: all
all: barebox.bin barebox.uimage

deploy-tftp undeploy-tftp:

.PHONY: barebox.bin
barebox.bin: .config
	$(MAKE) -f Makefile

.config:
	$(MAKE) -f Makefile vocore2_defconfig

.PHONY: help
help:
	@echo "U-Boot:"
	@echo " - environment \$${loadaddr}:"
	@echo "     tftp \$${loadaddr} barebox.bin; go \$${loadaddr}"
	@echo "     tftp \$${loadaddr} zbarebox.bin; go \$${loadaddr}"
	@echo "     tftp \$${loadaddr} barebox.uimage; bootm \$${loadaddr}"
	@echo "     md.b \$${loadaddr} 0x100"
	@if [ -e .config ]; then \
		echo " - CONFIG_TEXT_BASE/CONFIG_ARCH_TEXT_BASE:"; \
		sed -n '/^CONFIG_[A-Z_]*TEXT_BASE=/s,CONFIG_[A-Z_]*TEXT_BASE=0x\([0-9a-f]*\),     tftp 0x\1 barebox.bin; go 0x\1,p' .config; \
	fi
	@if [ -e barebox.map ]; then \
		echo " - main_entry:"; \
		sed -n \
		    -e 's,^ .text_entry *0x00000000\([0-9a-f]*\) .*$$,     tftp 0x\1 barebox.bin,p' \
		    -e 's,^ *0x00000000\([0-9a-f]*\) *main_entry$$,     go 0x\1,p' \
		    barebox.map; \
		sed -n \
		    -e 's,^ *0x00000000\([0-9a-f]*\) *main_entry$$,     md.b 0x\1 0x100,p' \
		    barebox.map; \
		echo " - start_barebox:"; \
		sed -n \
		    -e 's,^ .text_entry *0x00000000\([0-9a-f]*\) .*$$,     tftp 0x\1 barebox.bin,p' \
		    -e 's,^ *0x00000000\([0-9a-f]*\) *start_barebox$$,     go 0x\1,p' \
		    barebox.map; \
		sed -n \
		    -e 's,^ *0x00000000\([0-9a-f]*\) *start_barebox$$,     md.b 0x\1 0x100,p' \
		    barebox.map; \
	fi
	@if [ -e arch/mips/pbl/zbarebox.map ]; then \
		echo " - pbl_main_entry:"; \
		sed -n \
		    -e '/^ .text_head_entry/{n;s,^ *0x00000000\([0-9a-f]*\) .*$$,     tftp 0x\1 zbarebox.bin; go 0x\1,p}' \
		    -e 's,^ *0x00000000\([0-9a-f]*\) *pbl_main_entry$$,     go 0x\1,p' \
		    arch/mips/pbl/zbarebox.map; \
		sed -n \
		    -e 's,^ *0x00000000\([0-9a-f]*\) *pbl_main_entry$$,     md.b 0x\1 0x100,p' \
		    arch/mips/pbl/zbarebox.map; \
		echo " - pbl_start:"; \
		sed -n \
		    -e '/^ .text_head_entry/{n;s,^ *0x00000000\([0-9a-f]*\) .*$$,     tftp 0x\1 zbarebox.bin; go 0x\1,p}' \
		    -e 's,^ *0x00000000\([0-9a-f]*\) *pbl_start$$,     go 0x\1,p' \
		    arch/mips/pbl/zbarebox.map; \
		sed -n \
		    -e 's,^ *0x00000000\([0-9a-f]*\) *pbl_start$$,     md.b 0x\1 0x100,p' \
		    arch/mips/pbl/zbarebox.map; \
	fi
	@echo ""
	@echo "Host:"
	@echo " - Network:"
	@echo "   systemctl start tftpd.service"
	@echo "   ip addr add 192.168.1.3/24 dev enp0s25"
	@echo " - Serial:"
	@echo "   picocom -b 115200 /dev/ttyACM0"

.PHONY: connect-serial
.SILENT: connect-serial
connect-serial:
	while sleep 1; do \
		for tty in /dev/ttyACM*; do \
			if [ -e "$$tty" ]; then \
				echo "$(MAKE): Type [C-a] [C-q] to quit picocom"; \
				echo "$(MAKE): Type [C-c] to quit connect-serial"; \
				echo ""; \
				echo -n 4 >$$tty; \
				picocom -b 115200 $$tty; \
			fi ;\
		done; \
	done

.PHONY: clean
clean:
	rm -f barebox.img
	$(MAKE) -f Makefile $@

picocom-%:
	picocom -b 115200 /dev/tty$*

deploy-%:
	install -m 755 barebox.bin barebox.uimage /srv/$*/
	if [ -e arch/mips/pbl/zbarebox.bin ]; then \
		install -m 755 arch/mips/pbl/zbarebox.bin /srv/$*/; \
	fi

undeploy-%:
	rm -f /srv/$*/barebox.bin /srv/$*/barebox.uimage /srv/$*/zbarebox.bin

%:
	$(MAKE) -f Makefile $@

