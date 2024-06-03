# Lazy Page Allocation on xv6

## Author
**Mrugank Jadhav**

---

## Description
Lazy page allocation is a memory management technique used in operating systems, particularly in the x86 architecture, to optimize memory usage and performance. Instead of allocating physical memory for each page when it is requested, lazy page allocation delays the allocation until the page is actually accessed by the program.

### Implementation Details
1. **Page Fault Handling**: When a page that has not been allocated physical memory is accessed, a page fault occurs. The operating system's page fault handler then allocates physical memory for the page on demand.

2. **Virtual Memory Management**: Lazy page allocation relies on the concept of virtual memory, where each process has its own virtual address space. The mapping between virtual and physical memory is managed by the operating system's memory management unit (MMU).

3. **Page Table Entries**: Each process has a page table that maps its virtual addresses to physical addresses. Initially, these mappings are set to indicate that the pages are not present in physical memory.

4. **Page Allocation**: When a page fault occurs, the operating system allocates physical memory for the requested page and updates the page table entry to point to the allocated memory. This process is transparent to the running program.

5. **Demand Paging**: Lazy page allocation is often implemented together with demand paging, where pages are brought into physical memory only when they are needed. This helps to minimize the amount of physical memory required to run a program.

### Example
When we increase the size of our data segment by `sbrk(10)`, we don't allocate new pages right away. We create an illusion to the user program that we have increased the size of the data segment. When the user program tries to write to this newly increased memory, a page fault occurs as physical memory has not been allocated yet. We capture this page fault in the `trap()` function by comparing the trap number with `T_PGFLT` (14). Then we take the following actions to allocate the required pages.

---

## Test Cases
1. **Test 1: `sbrk(10)`**
2. **Test 2: Writing Valid Bytes**
3. **Test 3: `sbrk(+)` --> `sbrk(-)` --> Write**
4. **Test 4: `sbrk(3 pages)` --> Write in 1st/2nd Pages --> `sbrk(-1 page)` x3**
5. **Test 5: Allocating Too Much Memory**
6. **Test 6: Writing in an Unallocated Page Above the Program Break**

### Test Case Results
The results of the test cases can be found in the `TEST_CASES.txt` file.
