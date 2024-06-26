#include "types.h"
#include "stat.h"
#include "user.h"

void test_1()
{
    printf(1, "=========== TEST 1: sbrk(10) ===========\n");
    printf(1, "Before sbrk(10), break 0x%p ", sbrk(0));
    print_free_frame_cnt();
    printf(1, "Calling sbrk(10) ...\n");
    sbrk(10);
    printf(1, "After sbrk(10), break 0x%p ", sbrk(0));
    print_free_frame_cnt();
    printf(1, "\n");
}

void test_2()
{
    char *a;
    printf(1, "=========== TEST 2: writing valid bytes ===========\n");
    printf(1, "Before the write, break 0x%p ", sbrk(0));
    print_free_frame_cnt();
    printf(1, "Writing byte 0x%p ...\n", sbrk(0));
    a = sbrk(0);
    *a = 1;
    printf(1, "After the write, ");
    print_free_frame_cnt();
    a = a - 1;
    printf(1, "\n");
    printf(1, "Before the write, ");
    print_free_frame_cnt();
    printf(1, "Writing byte 0x%p ...\n", a);
    *a = 2;
    printf(1, "After the write, ");
    print_free_frame_cnt();
    printf(1, "\n");
}
void test_3()
{
    char *a;
    printf(1, "=========== TEST 3: sbrk(+) --> sbrk(-) --> write ===========\n");
    printf(1, "Before sbrk(+), break 0x%p ", sbrk(0));
    print_free_frame_cnt();
    printf(1, "Calling sbrk(16) ...\n");
    sbrk(16);
    printf(1, "After sbrk(+), break 0x%p ", sbrk(0));
    print_free_frame_cnt();
    printf(1, "\n");
    printf(1, "Before sbrk(-), break 0x%p ", sbrk(0));
    print_free_frame_cnt();
    printf(1, "Calling sbrk(-1) ...\n");
    sbrk(-1);
    printf(1, "After sbrk(-1), break 0x%p ", sbrk(0));
    print_free_frame_cnt();
    printf(1, "\n");
    a = sbrk(0);
    printf(1, "Before the write, ");
    print_free_frame_cnt();
    printf(1, "Writing byte 0x%p ...\n", a);
    *a = 2;
    printf(1, "After the write, ");
    print_free_frame_cnt();
    printf(1, "\n");
}

void test_4()
{
    char *a;
    printf(1, "===========TEST 4: sbrk(3 pages) --> write in 1st/2nd pages --> sbrk(-1 page) --> sbrk(-1 page) --> sbrk(-1 page)===========\n");
    printf(1, "Before the sbrk(3 pages), break 0x%p ", sbrk(0));
    print_free_frame_cnt();
    printf(1, "Calling sbrk(12288) ...\n");
    sbrk(12288);
    printf(1, "After the sbrk(3 pages), break 0x%p", sbrk(0));
    print_free_frame_cnt();
    printf(1, "\n");
    printf(1, "Before the write (in 1st page), ");
    print_free_frame_cnt();
    a = sbrk(0) - (4096 * 2);
    printf(1, "Writing byte 0x%p ...\n", a);
    *a = 1;
    printf(1, "After the write, ");
    print_free_frame_cnt();
    printf(1, "\n");
    printf(1, "Before the write (in 2nd page), ");
    print_free_frame_cnt();
    a = sbrk(0) - 4096;
    printf(1, "Writing byte 0x%p ...\n", a);
    *a = 1;
    printf(1, "After the write, ");
    print_free_frame_cnt();
    printf(1, "\n");
    printf(1, "Before the sbrk(-1 pages), break 0x%p ", sbrk(0));
    print_free_frame_cnt();
    printf(1, "Calling sbrk(-4096) ...\n");
    sbrk(-4096);
    printf(1, "After the sbrk(-1 pages), break 0x%p", sbrk(0));
    print_free_frame_cnt();
    printf(1, "\n");
    printf(1, "Before the sbrk(-1 pages), break 0x%p ", sbrk(0));
    print_free_frame_cnt();
    printf(1, "Calling sbrk(-4096) ...\n");
    sbrk(-4096);
    printf(1, "After the sbrk(-1 pages), break 0x%p", sbrk(0));
    print_free_frame_cnt();
    printf(1, "\n");
    printf(1, "Before the sbrk(-1 pages), break 0x%p ", sbrk(0));
    print_free_frame_cnt();
    printf(1, "Calling sbrk(-4096) ...\n");
    sbrk(-4096);
    printf(1, "After the sbrk(-1 pages), break 0x%p ", sbrk(0));
    print_free_frame_cnt();
    printf(1, "\n");
}

void test_5()
{
    printf(1, "=========== TEST 5: allocating too much memory ===========\n");
    printf(1, "Before the sbrk(0x7FFFFFFF), break 0x%p ", sbrk(0));
    print_free_frame_cnt();
    printf(1, "Calling sbrk(0x7FFFFFFF) ...\n");
    sbrk(0x7FFFFFFF);
    printf(1, "After the sbrk(0x7FFFFFFF), break 0x%p ", sbrk(0));
    print_free_frame_cnt();
    printf(1, "\n");
}
void test_6()
{
    char *a;
    printf(1, "=========== TEST 6: writing in a unallocated page above the progam break ===========\n");
    printf(1, "Before the write, break 0x%p ", sbrk(0));
    print_free_frame_cnt();
    a = sbrk(0) + 4096;
    printf(1, "Writing byte 0x%p ...\n", a);
    *a = 1;
    printf(1, "After the write, ");
    print_free_frame_cnt();
    printf(1, "\n");
}

int main(int argc, char *argv[])
{
    int ind = 0;
    if (argc < 2)
    {
        printf(1, "Usage: alloc_test 0|1.\n"
                  "\t0: DEFAULT Allocation.\n"
                  "\t1: Lazy Page Allocation.\n");
        exit();
    }

    if (argv[1][0] == '0')
    {
        ind = 0;
        printf(1, "\nDefault Page Allocator ...\n");
    }
    else
    {
        ind = 1;
        printf(1, "\nLazy Page Allocator ...\n");
    }

    set_page_allocator(ind); // set according to user input
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    test_6();
    exit();
    return 0;
}