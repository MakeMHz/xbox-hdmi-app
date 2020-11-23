XBE_TITLE = XboxHDMI
GEN_XISO = $(XBE_TITLE).iso
NXDK_CXX = y
NXDK_SDL = y
DEBUG = y
CFLAGS="-D_XBOX"
CXXFLAGS="-D_XBOX"

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
