/*
 * monitor.h - The VICE built-in monitor, external interface.
 *
 * Written by
 *  Andreas Boose <viceteam@t-online.de>
 *  Daniel Sladic <sladic@eecg.toronto.edu>
 *  Ettore Perazzoli <ettore@comm2000.it>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

#ifndef _MONITOR_H
#define _MONITOR_H

#include "types.h"

/** Generic interface.  **/
#define NUM_MEMSPACES 6

#define any_watchpoints(mem) \
    (watchpoints_load[(mem)] || watchpoints_store[(mem)])

enum mon_int {
    MI_NONE = 0,
    MI_BREAK = 1 << 0,
    MI_WATCH = 1 << 1,
    MI_STEP = 1 << 2
};

enum t_memspace {
   e_default_space = 0,
   e_comp_space,
   e_disk8_space,
   e_disk9_space,
   e_disk10_space,
   e_disk11_space,
   e_invalid_space
};
typedef enum t_memspace MEMSPACE;

enum CPU_TYPE_s {
    CPU_6502,
    CPU_Z80
};
typedef enum CPU_TYPE_s CPU_TYPE_t;

struct interrupt_cpu_status_s;

struct monitor_cpu_type_s {
    CPU_TYPE_t cpu_type;
    unsigned int (*asm_addr_mode_get_size)(unsigned int mode, BYTE p0,
                                           BYTE p1);
    const struct asm_opcode_info_s *(*asm_opcode_info_get)(BYTE p0, BYTE p1,
                                                           BYTE p2);
    int (*mon_assemble_instr)(const char *opcode_name, unsigned int operand);
    unsigned int (*mon_register_get_val)(int mem, int reg_id);
    void (*mon_register_set_val)(int mem, int reg_id, WORD val);
    void (*mon_register_print)(int mem);
    struct mon_reg_list_s *(*mon_register_list_get)(int mem);
    void (*mon_register_list_set)(struct mon_reg_list_s *mon_reg_list, int mem);
};
typedef struct monitor_cpu_type_s monitor_cpu_type_t;

/* This is the standard interface through which the monitor accesses a
   certain CPU.  */
struct monitor_interface_s {
    /* Pointer to the registers of the 6502 CPU.  */
    struct mos6510_regs_s *cpu_regs;

    /* Pointer to the registers of the Z80 CPU.  */
    struct z80_regs_s *z80_cpu_regs;

    /* Pointer to the alarm/interrupt status.  */
    struct interrupt_cpu_status_s *int_status;

    /* Pointer to the machine's clock counter.  */
    CLOCK *clk;

    int current_bank;
    const char **(*mem_bank_list)(void);
    int (*mem_bank_from_name)(const char *name);
    BYTE (*mem_bank_read)(int bank, WORD addr, void *context);
    BYTE (*mem_bank_peek)(int bank, WORD addr, void *context);
    void (*mem_bank_write)(int bank, WORD addr, BYTE byte, void *context);

    struct mem_ioreg_list_s *(*mem_ioreg_list_get)(void *context);

    /* Pointer to a function to disable/enable watchpoint checking.  */
    /*monitor_toggle_func_t *toggle_watchpoints_func;*/
    void (*toggle_watchpoints_func)(int value, void *context);

    /* Update bank base (used for drives).  */
    void (*set_bank_base)(void *context);

    void (*get_line_cycle)(unsigned int *line, unsigned int *cycle, int *half_cycle);

    void *context;
};
typedef struct monitor_interface_s monitor_interface_t;

/* Externals */
struct break_list_s;
extern struct break_list_s *watchpoints_load[NUM_MEMSPACES];
extern struct break_list_s *watchpoints_store[NUM_MEMSPACES];
extern struct break_list_s *breakpoints[NUM_MEMSPACES];

extern MEMSPACE caller_space;
extern unsigned monitor_mask[NUM_MEMSPACES];


/* Prototypes */
extern void monitor_init(monitor_interface_t *maincpu_interface,
                         monitor_interface_t *drive_interface_init[],
                         struct monitor_cpu_type_s **asmarray);
extern void monitor_shutdown(void);
extern int monitor_cmdline_options_init(void);
extern void monitor_startup(void);
extern void monitor_startup_trap(void);

extern void monitor_abort(void);

extern int monitor_force_import(MEMSPACE mem);
extern void monitor_check_icount(WORD a);
extern void monitor_check_icount_interrupt(void);
extern void monitor_check_watchpoints(WORD a);

extern void monitor_cpu_type_set(const char *cpu_type);

extern void monitor_watch_push_load_addr(WORD addr, MEMSPACE mem);
extern void monitor_watch_push_store_addr(WORD addr, MEMSPACE mem);

extern monitor_interface_t *monitor_interface_new(void);
extern void monitor_interface_destroy(monitor_interface_t *monitor_interface);

extern int monitor_diskspace_dnr(int mem);
extern int monitor_diskspace_mem(int dnr);

/** Breakpoint interface.  */
/* Defines */
#define monitor_check_breakpoints(mem, addr) \
    monitor_breakpoint_check_checkpoint(mem, addr, breakpoints[mem])

/* Prototypes */
extern int monitor_breakpoint_check_checkpoint(MEMSPACE mem, WORD addr,
                                               struct break_list_s *list);

/** Disassemble interace */
/* Prototypes */
extern const char *mon_disassemble_to_string(MEMSPACE, WORD addr, BYTE x,
                                             BYTE p1, BYTE p2, BYTE p3,
                                             int hex_mode,
                                             const char *cpu_type);

/** Register interface.  */
extern struct mon_reg_list_s *mon_register_list_get(int mem);
extern void mon_ioreg_add_list(struct mem_ioreg_list_s **list, const char *name,
                               WORD start, WORD end);

/* Assembler initialization.  */
extern void asm6502_init(struct monitor_cpu_type_s *monitor_cpu_type);
extern void asmz80_init(struct monitor_cpu_type_s *monitor_cpu_type);

struct monitor_cartridge_commands_s {
    int (*cartridge_attach_image)(int type, const char *filename);
    void (*cartridge_detach_image)(void);
    void (*cartridge_trigger_freeze)(void);
    void (*cartridge_trigger_freeze_nmi_only)(void);
};
typedef struct monitor_cartridge_commands_s monitor_cartridge_commands_t;

extern monitor_cartridge_commands_t mon_cart_cmd;

/* CPU history/memmap prototypes */
extern void monitor_cpuhistory_store(WORD addr, BYTE op, BYTE p1, BYTE p2);
extern void monitor_memmap_store(unsigned int addr, BYTE type);

/* memmap defines */
#define MEMMAP_I_O_R 0x80
#define MEMMAP_I_O_W 0x40
#define MEMMAP_ROM_R 0x20
#define MEMMAP_ROM_W 0x10
#define MEMMAP_ROM_X 0x08
#define MEMMAP_RAM_R 0x04
#define MEMMAP_RAM_W 0x02
#define MEMMAP_RAM_X 0x01

/* HACK to enable fetch/load separation */
extern BYTE memmap_state;
#define MEMMAP_STATE_IGNORE 0x04
#define MEMMAP_STATE_INSTR  0x02
#define MEMMAP_STATE_OPCODE 0x01

#endif

