PKG_NAME=riot-tee-bl
PKG_URL=https://github.com/janthies/riot-tee-bl.git
PKG_VERSION=efa3937a295513a4a707e377cab09c11630a7acd
PKG_LICENSE=LGPL-2.1-only

include $(RIOTBASE)/pkg/pkg.mk

TOOLCHAIN_FILE=$(PKG_BUILD_DIR)/xcompile-toolchain.cmake

all: $(PKG_BUILD_DIR)/Makefile
	$(MAKE) -C $(PKG_BUILD_DIR)

# The toolchain file also carries the CFLAGS of the application, such as
# riotbuild.h and NRF_TRUSTZONE_NONSECURE. The bootloader is an image of its own
# and sets its flags in its CMakeLists.txt, so CMAKE_C_FLAGS is cleared.
$(PKG_BUILD_DIR)/Makefile: $(TOOLCHAIN_FILE)
	@rm -rf $(PKG_BUILD_DIR)/CMakeCache.txt
	git -C $(PKG_SOURCE_DIR) submodule update --init --recursive
	cmake \
		-DCMAKE_BUILD_TYPE=MinSizeRel \
		-DCMAKE_C_FLAGS="" \
		-DTOOLCHAINPATH=/usr/bin \
		-DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN_FILE) \
		-DBL_FLASH_SIZE=$(BL_FLASH_SIZE) \
		-DTEE_FLASH_START=$(TEE_FLASH_START) \
		-DTEE_FLASH_SIZE=$(TEE_FLASH_SIZE) \
		-DTFM_PATH=$(PKGDIRBASE)/tf-m \
		-B$(PKG_BUILD_DIR) \
		-H$(PKG_SOURCE_DIR)

$(TOOLCHAIN_FILE):
	mkdir -p $(PKG_BUILD_DIR)
	$(RIOTTOOLS)/cmake/generate-xcompile-toolchain.sh > $(TOOLCHAIN_FILE)
