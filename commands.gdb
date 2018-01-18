target extended localhost:4242
tui enable
# b init.c:221
# c
# b create_pagetables
# b page_index_to_pa
# b start_loader
# b mem_init
# b diag_init
# b diag_driver_init
# b fdt_getprop
# b *0x40200000
# j *0x40200000
# file ./test
# b after_jump
# continue
# b printf.c:354
# layout asm
# info registers
# stepi
