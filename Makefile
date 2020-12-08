XBE_TITLE = XboxHDMI
GEN_XISO = $(XBE_TITLE).iso
NXDK_CXX = y
NXDK_SDL = y
DEBUG = y
CFLAGS="-D_XBOX"
CXXFLAGS="-D_XBOX"

NXDK_DIR ?= $(CURDIR)/../nxdk

ASSETS_DIR = $(OUTPUT_DIR)/assets

SRCS += $(CURDIR)/source/main.cpp
SRCS += $(CURDIR)/source/common.cpp
SRCS += $(CURDIR)/source/crc32.cpp
SRCS += $(CURDIR)/source/console.cpp
SRCS += $(CURDIR)/source/scene.cpp
SRCS += $(CURDIR)/source/scene0.cpp
SRCS += $(CURDIR)/source/scene1.cpp
SRCS += $(CURDIR)/source/scene2.cpp
SRCS += $(CURDIR)/source/scene3.cpp
SRCS += $(CURDIR)/source/scene4.cpp


include $(NXDK_DIR)/Makefile

TARGET += $(ASSETS_DIR)
$(GEN_XISO): $(ASSETS_DIR)

$(ASSETS_DIR):
	$(VE)cp -R $(patsubst $(OUTPUT_DIR)%,$(CURDIR)%,$@) '$@'
