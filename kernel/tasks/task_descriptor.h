#ifndef TASK_DESCRIPTOR_H
#define TASK_DESCRIPTOR_H
#include <stdint.h>
#include <stdbool.h>
#include "../memory/pdt.h"
#include "../memory/pt.h"
#include "../memory/page_allocator.h"
#include "../isr.h"

struct task_desc {
    struct pde * page_directory;
    bool         userspace;
    registers_t  context;
};

#endif /* ifndef TASK_DESCRIPTOR_H */
