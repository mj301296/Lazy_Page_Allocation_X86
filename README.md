# Lazy_Page_Allocation_X86


NAME: MRUGANK JADHAV
---------------------------------------------------------------------------------------------------------------------

DESCRIPTION:
Lazy page allocation is a memory management technique used in operating systems, particularly in the x86 architecture, to optimize memory usage and performance. Instead of allocating physical memory for each page when it is requested, lazy page allocation delays the allocation until the page is actually accessed by the program.

Implementation Details:

Page Fault Handling: When a page that has not been allocated physical memory is accessed, a page fault occurs. The operating system's page fault handler then allocates physical memory for the page on demand.

Virtual Memory Management: Lazy page allocation relies on the concept of virtual memory, where each process has its own virtual address space. The mapping between virtual and physical memory is managed by the operating system's memory management unit (MMU).

Page Table Entries: Each process has a page table that maps its virtual addresses to physical addresses. Initially, these mappings are set to indicate that the pages are not present in physical memory.

Page Allocation: When a page fault occurs, the operating system allocates physical memory for the requested page and updates the page table entry to point to the allocated memory. This process is transparent to the running program.

Demand Paging: Lazy page allocation is often implemented together with demand paging, where pages are brought into physical memory only when they are needed. This helps to minimize the amount of physical memory required to run a program.

Example:
When we increase the size of our data segment by sbrk(10), we dont allocate new page right away. We create 
an illusion to the user program that we have increased the size of the data segment. When user program
tries to write to this newly increased memory, page fault occurs as physical memory has not been allocated
yet. We capture this page fault in trap() function by comparing trap number with T_PGFLT (14). Then we take
following actions to allocate required pages.

---------------------------------------------------------------------------------------------------------------------

TEST CASE:
$lazyallocation 0

Default Page Allocator ...
=========== TEST 1: sbrk(10) ===========
Before sbrk(10), break 0x4000 free-frames 56789
Calling sbrk(10) ...
After sbrk(10), break 0x400A free-frames 56788

=========== TEST 2: writing valid bytes ===========
Before the write, break 0x400A free-frames 56788
Writing byte 0x400A ...
After the write, free-frames 56788

Before the write, free-frames 56788
Writing byte 0x4009 ...
After the write, free-frames 56788

=========== TEST 3: sbrk(+) --> sbrk(-) --> write ===========
Before sbrk(+), break 0x400A free-frames 56788
Calling sbrk(16) ...
After sbrk(+), break 0x401A free-frames 56788

Before sbrk(-), break 0x401A free-frames 56788
Calling sbrk(-1) ...
After sbrk(-1), break 0x4019 free-frames 56788

Before the write, free-frames 56788
Writing byte 0x4019 ...
After the write, free-frames 56788

===========TEST 4: sbrk(3 pages) --> write in 1st/2nd pages --> sbrk(-1 page) --> sbrk(-1 page) --> sbrk(-1 page)===========
Before the sbrk(3 pages), break 0x4019 free-frames 56788
Calling sbrk(12288) ...
After the sbrk(3 pages), break 0x7019free-frames 56785

Before the write (in 1st page), free-frames 56785
Writing byte 0x507D ...
After the write, free-frames 56785

Before the write (in 2nd page), free-frames 56785
Writing byte 0x607D ...
After the write, free-frames 56785

Before the sbrk(-1 pages), break 0x7019 free-frames 56785
Calling sbrk(-4096) ...
After the sbrk(-1 pages), break 0x6019free-frames 56786

Before the sbrk(-1 pages), break 0x6019 free-frames 56786
Calling sbrk(-4096) ...
After the sbrk(-1 pages), break 0x5019free-frames 56787

Before the sbrk(-1 pages), break 0x5019 free-frames 56787
Calling sbrk(-4096) ...
After the sbrk(-1 pages), break 0x4019free-frames 56788

=========== TEST 5: allocating too much memory ===========
Before the sbrk(0x7FFFFFFF), break 0x4019 free-frames 56788
Calling sbrk(0x7FFFFFFF) ...
Allocating pages failed!
After the sbrk(0x7FFFFFFF), break 0x4019free-frames 56788

=========== TEST 6: writing in a unallocated page above the progam break ===========
Before the write, break 0x4019free-frames 56788
Writing byte 0x5019 ...
Unhandled Page Fault.
pid 4 lazyallocation: trap 14 err 6 on cpu 0 eip 0x75a addr 0x5019--kill proc

$lazyallocation 1
Lazy Page Allocator ...
=========== TEST 1: sbrk(10) ===========
Before sbrk(10), break 0x4000 free-frames 56789
Calling sbrk(10) ...
After sbrk(10), break 0x400A free-frames 56789

=========== TEST 2: writing valid bytes ===========
Before the write, break 0x400A free-frames 56789
Writing byte 0x400A ...
After the write, free-frames 56788

Before the write, free-frames 56788
Writing byte 0x4009 ...
After the write, free-frames 56788

=========== TEST 3: sbrk(+) --> sbrk(-) --> write ===========
Before sbrk(+), break 0x400A free-frames 56788
Calling sbrk(16) ...
After sbrk(+), break 0x401A free-frames 56788

Before sbrk(-), break 0x401A free-frames 56788
Calling sbrk(-1) ...
After sbrk(-1), break 0x4019 free-frames 56788

Before the write, free-frames 56788
Writing byte 0x4019 ...
After the write, free-frames 56788

===========TEST 4: sbrk(3 pages) --> write in 1st/2nd pages --> sbrk(-1 page) --> sbrk(-1 page) --> sbrk(-1 page)===========
Before the sbrk(3 pages), break 0x4019 free-frames 56788
Calling sbrk(12288) ...
After the sbrk(3 pages), break 0x7019free-frames 56788

Before the write (in 1st page), free-frames 56788
Writing byte 0x507D ...
After the write, free-frames 56787

Before the write (in 2nd page), free-frames 56787
Writing byte 0x607D ...
After the write, free-frames 56786

Before the sbrk(-1 pages), break 0x7019 free-frames 56786
Calling sbrk(-4096) ...
After the sbrk(-1 pages), break 0x6019free-frames 56786

Before the sbrk(-1 pages), break 0x6019 free-frames 56786
Calling sbrk(-4096) ...
After the sbrk(-1 pages), break 0x5019free-frames 56787

Before the sbrk(-1 pages), break 0x5019 free-frames 56787
Calling sbrk(-4096) ...
After the sbrk(-1 pages), break 0x4019free-frames 56788

=========== TEST 5: allocating too much memory ===========
Before the sbrk(0x7FFFFFFF), break 0x4019 free-frames 56788
Calling sbrk(0x7FFFFFFF) ...
Allocating pages failed!
After the sbrk(0x7FFFFFFF), break 0x4019free-frames 56788

=========== TEST 6: writing in a unallocated page above the progam break ===========
Before the write, break 0x4019free-frames 56788
Writing byte 0x5019 ...
Unhandled Page Fault.
pid 4 lazyallocation: trap 14 err 6 on cpu 0 eip 0x75a addr 0x5019--kill proc
---------------------------------------------------------------------------------------------------------------------
