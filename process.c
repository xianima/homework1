#include "process.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int MakeBlock(struct Die *die, struct Power *power,struct Block *block,int num_power_data, float sum_in_power)
{
    //caculate the length of each block
    float blocklength_x,blocklength_y;
    blocklength_x=(die->upper_right_x - die->lower_left_x)/die->num_of_block_x;
    blocklength_y=(die->upper_right_y - die->lower_left_y)/die->num_of_block_y;
    
    float sum_out_power=0;
    float power_block[die->num_of_block];
    for(int i=0 ;i<die->num_of_block;i++)
    {
        power_block[i]=0;
    }
    
    //calculate which block the power is distributed on
    int x_th,y_th;
    for(int i=0;i<num_power_data;i++)
    {
        if(power->power_value!=0)
        {
            x_th=(int)((power->location_x - die->lower_left_x)/blocklength_x);
            y_th=(int)((power->location_y - die->lower_left_y)/blocklength_y);

            //conside the right and upper boundary 
        if(x_th==die->num_of_block_x)
            x_th--;
        if(y_th==die->num_of_block_y)
            y_th--;

            power_block[x_th+y_th * die->num_of_block_x]+=power->power_value;

            power++;
        }
    }

    //caculate the parameter of each block and assign the power of the block 
    for(int i=0;i<die->num_of_block;i++)
    {
        int x=i%die->num_of_block_x;//the number of x direction
        int y=i/die->num_of_block_x;//the number of y direction
        
        block->lower_left_x = die->lower_left_x + blocklength_x * x;
        block->lower_left_y = die->lower_left_y + blocklength_y * y;
        block->upper_right_x = die->lower_left_x + blocklength_x * (x+1);
        block->upper_right_y = die->lower_left_y + blocklength_y * (y+1);
        block->power_value = power_block[i];

        sum_out_power+=power_block[i];
        block++;
    }

    if(abs(sum_in_power-sum_out_power)/sum_in_power<0.1)
        return 0;
    else
        return 1;
    
}