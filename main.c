#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#include "input.h"
#include "process.h"
#include "output.h"

#define STR_SIZE 512


void Usage(int argc, char **argv)
{
    printf("Usage: %s -c <file> -p <file> -o <file> \n",argv[0]);
    printf("\t-c <file> config input file(e.g.config.txt)\n");
    printf("\t-p <file> power input file(e.g.power.txt)\n");
    printf("\t-o <file> output file(is not necessary)\n");
}

void GetFileName(int argc, char **argv, char str, char* name)
{
    int f=0;//验证是否找到
    for(int i=1;i<argc;i+=2)
    {
        if(argv[i][0]!='-')
        {
            printf("error commands\n");
            exit(1);
        }
        if(str==argv[i][1])
        {
            strcpy(name,argv[i+1]);
            f=1;
        }
    }
    if(str=='c'&&f==0)
    {
        printf("no find config file\n");
        exit(1);
    }
    if(str=='p'&&f==0)
    {
        printf("no find power file\n");
        exit(1);
    }
    if(str=='o'&&f==0)
    {
        strcpy(name,"output.txt");
        printf("no find output file\n");
        printf("default output file is output.txt\n");
    }
    f=0;
}

int main(int argc, char **argv)
{

    struct Die die;
    struct Power *power;
    struct Block *block;

    int num_power_data;
    int num_block;
    float sum_in_power;

    char config_file[STR_SIZE],power_file[STR_SIZE],output_file[STR_SIZE];

    if(!(argc >= 5 && argc % 2))
    {
        printf("error commands\n");
        Usage(argc,argv);
        return 1;
    }

    GetFileName(argc, argv, 'c', config_file);
    GetFileName(argc, argv, 'p', power_file);
    GetFileName(argc, argv, 'o', output_file);

    ReadConfig(config_file,&die);

    num_power_data = CountPowerData(power_file);
    num_block = die.num_of_block;

    //allocating space to struct power and block
    power = calloc(num_power_data,sizeof(struct Power));
    block = calloc(num_block, sizeof(struct Block));
    
    sum_in_power=ReadPower(power_file,power);

    CheckInputData(&die, power, num_power_data);

    if(MakeBlock(&die,power,block,num_power_data,sum_in_power))
        printf("warring: input power is not equal to output power!!!\n");

    OutputToFile(block , die.num_of_block, output_file);


    // //test read file
    // printf("%s %s %s \n",config_file,power_file,output_file);
    // //test input
    // printf("%d %d %d %f %f \n",die.num_of_block_x,die.num_of_block_y,die.num_of_block,die.lower_left_x,die.upper_right_y);
    // printf("%d\n",num_power_data);
    // for(int i=0;i<num_power_data;i++)
    // {
    //         printf("%f %f %f\n",power[i].location_x,power[i].location_y,power[i].power_value);
    // }

    // //test process
    // for(int i=0;i<die.num_of_block;i++)
    // {
    //     printf("%f %f %f %f %f\n",block[i].lower_left_x,block[i].lower_left_y,block[i].upper_right_x,block[i].upper_right_y,block[i].power_value);
    // }
    
    
    free(power);
    free(block);

    return 0;
}