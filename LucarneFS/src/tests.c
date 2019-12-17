#include "../headers/lucarnefs.h"
#include <stdio.h>
#include "../headers/tests.h"

int test_sizes()
{
    printf("%d\n", sizeof(struct LuFS_volume_identifier));
    printf("%d\n", sizeof(struct LuFS_block_pointer));
    printf("%d\n", sizeof(struct LuFS_master_block));
    printf("%d\n", sizeof(struct LuFS_folder_block));
    printf("%d\n", sizeof(struct LuFS_file_block));
    printf("%d\n", sizeof(struct LuFS_data_block));
    return 0;
}
