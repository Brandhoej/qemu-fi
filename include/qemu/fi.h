#ifndef QEMU_FI_H
#define QEMU_FI_H

#include <stddef.h>
#include <stdint.h>

#include "exec/cpu-defs.h"
#include "typedefs.h"

// Maximum number of fault injections.
#define MAX_FIS 32

/* All attacks so far are adopted to CPUARchState where there is:
 * 1. General purpose registers (target_ulong) "gpr[32]"
 * 2. General purpose _half_ registers (target_ulong) "gprh[32]" 
 * Where grph is the upper half for 128-bit registers. */

// Bit-Flip Register (BFR) attack. Models BFR attacks as register bit-flips on the transition between instructions.
typedef struct BFR {
    // The source as the instruction offset.
    target_ulong source;
    // The destination as the instruction offset.
    target_ulong destination;
    // The mask describing the bits to flip.
    target_ulong mask;
    // The upper-half mask for the bits to flip in the gprh register.
    target_ulong mask_h;
    // The logical counter for the time-to-attack.
    int32_t counter;
    // The index of the register in cpu_R.
    uint8_t reg;
} BFR;

// Instruction Skip (IS) attack. Models IS attacks as a single instruction which can be skipped. 
typedef struct IS {
    // The instruction to skip.
    target_ulong pc;
    // The logical counter for the time-to-attack.
    int32_t counter;
} IS;

// Instruction Corruption (IC) attack. Models IC attacks by flipping the mask on the instruction.
typedef struct IC {
    // The instruction to corrupt.
    target_ulong pc;
    // The mask describing the bits to flip.
    int32_t mask;
    // The logical counter for the time-to-attack.
    int32_t counter;
} IC;

typedef enum AttackType {
    ATTACK_BFR,
    ATTACK_IS,
    ATTACK_IC,
} AttackType;

typedef union AttackStrategy {
    BFR bfr;
    IS is;
    IC ic;
} AttackStrategy;

typedef struct Attack {
    AttackType type;
    AttackStrategy strategy;
} Attack;

void fi_init_strategy(Attack attacks[MAX_FIS], size_t number_of_attacks);

#endif