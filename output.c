#include "output.h"

#include <stdio.h>
#include <stdlib.h>


void OutputToFile(struct Block *block,int num_block,char* file)
{
    FILE *fp=fopen(file,"w");
    if(fp==NULL)
    {
        printf("output.txt open error\n");
        exit(1);
    }    
    fprintf(fp,"# block lower left x    block lower left y    block upper right x    block upper right y    block power value\n");
    for(int i=0;i<num_block;i++)
    {
        fprintf(fp,"  %4.1f    %4.1f    %4.1f    %4.1f    %4.1f\n",block->lower_left_x,block->lower_left_y,block->upper_right_x,block->upper_right_y,block->power_value);
        block++;
    }
    fclose(fp);
}