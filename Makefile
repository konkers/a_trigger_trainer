NAME = att
SOURCES=reset.s asm4c.s main.c mem_pages.c
CONFIG=nes.cfg

CC65 = cc65
CA65 = ca65
LD65 = ld65

C_SRCS = $(filter %.c,$(SOURCES))
ASM_SRCS = $(filter %.s,$(SOURCES))
OBJS = $(addprefix out/obj/,$(C_SRCS:.c=.o) $(ASM_SRCS:.s=.o))

MAKE_TARGET_DIR = @mkdir -p $(dir $@)

out/$(NAME).nes: $(OBJS) $(CONFIG)
	$(LD65) -C $(CONFIG) -o $@ $(filter %.o,$^) nes.lib

out/obj/%.o: %.s
	$(MAKE_TARGET_DIR)
	$(CA65) -o $@ $<

out/obj/%.o: out/obj/%.s
	$(MAKE_TARGET_DIR)
	$(CA65) -o $@ $<

out/obj/%.s: %.c
	$(MAKE_TARGET_DIR)
	$(CC65) -Oi --add-source --create-dep $@.d -o $@ $<

clean:
	rm -rf out

-include $(addprefix out/obj/,$(C_SRCS:.c=.s.d))
