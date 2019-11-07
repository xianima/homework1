#ifndef INPUT_H
#define INPUT_H

#define MaxPowerData 100
#define MaxBlockData 100

struct Die
{
    int num_of_block_x;
    int num_of_block_y;
    int num_of_block;
    float lower_left_x;
    float lower_left_y;
    float upper_right_x;
    float upper_right_y;
};

struct Power
{
    float location_x;
    float location_y;
    float power_value;
};

struct Block
{
    float lower_left_x;
    float lower_left_y;
    float upper_right_x;
    float upper_right_y;
    float power_value;
};


void ReadConfig(char *name , struct Die *die);
float ReadPower(char *name , struct Power *power);
int CountPowerData(char *name);
void CheckInputData(struct Die *die, struct Power *power, int num_power_data);

#endif