MODULE := engines/supernova2

MODULE_OBJS := \
	detection.o \
	state.o \
	graphics.o \
	resman.o \
	rooms.o \
	screen.o \
	console.o \
	supernova2.o

MODULE_DIRS += \
	engines/supernova2

# This module can be built as a plugin
ifeq ($(ENABLE_SUPERNOVA2), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
