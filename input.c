#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE		512
#define LINE_SIZE		65536
//#define MAX_ENTRIES		512 //prevent dead loop

//input a config file 
//output a die struct  
void ReadConfig(char *file , struct Die *die)
{
    FILE * fp =fopen(file , "r");
    if(fp == NULL)
    {
        printf("open config file error\n");
        exit(1);
    }

    char line_data[LINE_SIZE],copy[LINE_SIZE];
    char *pstr;
    int count=0;
    int next_break=0;
    while(1)
    {
        fgets(line_data,LINE_SIZE,fp);
        if(feof(fp))
            if((line_data[0]=='\n')||(next_break==1))
                break;
            else
                next_break=1;
            
        
        strcpy(copy,line_data);

        //ignore comments and empty lines
        pstr = strtok(line_data," \0\r\t\n");
        if(!pstr || pstr[0]== '#' || pstr=="\r\n")
            continue;
        
        if(count==0)
            sscanf(copy,"%d", &die->num_of_block_x);
        if(count==1)
            sscanf(copy, "%d", &die->num_of_block_y);
        if(count==2)
            sscanf(copy, "%f%f", &die->lower_left_x,&die->lower_left_y);
        if(count==3)
            sscanf(copy, "%f%f", &die->upper_right_x,&die->upper_right_y);
        count++;
    }
    if(count!=4)
    {
        printf("the input config file is wrong\n");
        exit(1);
    }

    die->num_of_block=die->num_of_block_x*die->num_of_block_y;

    if(fclose(fp)==-1)
        printf("close error");
    
}

//input a power file
//return a number of power data
int CountPowerData(char *file)
{
    FILE * fp =fopen(file , "r");
    if(fp == NULL)
    {
        printf("open power file error\n");
        exit(1);
    }

    char line_data[LINE_SIZE];
    char *pstr;
    int count=0;
    int next_break=0;
    while(1)
    {
        fgets(line_data,LINE_SIZE,fp);
        if(feof(fp))
            if((line_data[0]=='\n')||(next_break==1))
                break;
            else
                next_break=1;

        //ignore comments and empty lines
        pstr = strtok(line_data," \r\t\n");
        if(!pstr || pstr[0]== '#')
            continue;
        
        count++;
    }
    if(fclose(fp)==-1)
        printf("close error");
        
    return count;
}

//input a power file 
//output a power struct  
float ReadPower(char *file , struct Power *power)
{
    FILE * fp =fopen(file , "r");
    if(fp == NULL)
    {
        printf("open power file error\n");
        exit(1);
    }

    char line_data[LINE_SIZE],copy[LINE_SIZE];
    char *pstr;
    int next_break=0;
    float sum_power=0;
    while(1)
    {

        fgets(line_data,LINE_SIZE,fp);
        if(feof(fp))
            if((line_data[0]=='\n')||(next_break==1))
                break;
            else
                next_break=1;
        
        strcpy(copy,line_data);

        //ignore comments and empty lines
        pstr = strtok(line_data," \r\t\n");
        if(!pstr || pstr[0]== '#')
            continue;
        
        sscanf(copy, "%f %f %f", &power->location_x,&power->location_y,&power->power_value);
        sum_power+=power->power_value;
        power++;
    }
    
    if(fclose(fp)==-1)
        printf("close error");

    return sum_power;
    
}

//intput data from config and power file
//check the data for logical problems 
void CheckInputData(struct Die *die, struct Power *power, int num_power_data)
{
    if(die->num_of_block_x<=0 || die->num_of_block_y<=0 || die->lower_left_x>=die->upper_right_x || die->lower_left_y>=die->upper_right_y)
    {
        printf("error data in config file\n");
        exit(1);
    }
    for(int i=0;i<num_power_data;i++)
    {
        if(power->location_x<die->lower_left_x||power->location_x>die->upper_right_x
            ||power->location_y<die->lower_left_y||power->location_y>die->upper_right_y
            ||power->power_value<0)
        {
            printf("error data in power file\n");
            exit(1);
        }
    }
}