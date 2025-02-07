#ifndef QEMU_FI_H
#define QEMU_FI_H

#include <stddef.h>
#include <stdint.h>

#include "exec/cpu-defs.h"
#include "typedefs.h"

// Maximum number of fault injections.
#define MAX_FIS 32

// Bit-Flip Register (BFR) attack. The model bases BFR attacks to happen between the execution of instructions.
typedef struct BFR {
    // The source as the instruction offset.
    target_ulong source;
    // The destination as the instruction offset.
    target_ulong destination;
    // The mask describing the bits to flip.
    int32_t mask;
    // The logical counter for the time-to-attack.
    int32_t counter;
    // The index of the register in cpu_R.
    uint8_t reg;
} BFR;

void fi_init_strategy(BFR array[MAX_FIS], size_t array_size);

#endif