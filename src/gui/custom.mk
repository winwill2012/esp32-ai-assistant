CUSTOM_CSRCS += $(shell find -L $(PRJ_DIR)/custom -name "*.c")
GEN_CSRCS += $(subst $(PRJ_DIR)/custom/,,$(CUSTOM_CSRCS))

DEPPATH += --dep-path $(PRJ_DIR)/custom
VPATH += :$(PRJ_DIR)/custom

CFLAGS += "-I$(PRJ_DIR)/custom"