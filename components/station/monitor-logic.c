#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "i2cmaster.h"
#include "utility.c"

int occupiedIndex = 0;
int monitorIndex = 1;

bool isConnected = false;
bool isAlreadyBeenRead = false;

#define SLA 0x05

void evaluateConfig(int config[6]);

int main()
{
    while (true)
    {
        isConnected = checkI2CConnection(SLA);

        if (isConnected)
        {
            if (!isAlreadyBeenRead)
            {
                int config[6];
                readConfig(config, SLA);
                evaluateConfig(config);
                isAlreadyBeenRead = true;
            }
        }
        else
        {
            isAlreadyBeenRead = false;
        }

        delay(500);
    }

    return 0;
}

void evaluateConfig(int config[6])
{
    // if slot isnt occupied do nothing
    // if slot is occupied set monitorbit.
    // if slot is occupied and monitorbit is already set (that means unchanged after one round), an error happened on the station -> set slot to empty
    if(config[occupiedIndex] == 1)
    {
        if(config[monitorIndex] == 1)
        {
            config[occupiedIndex] = 0;
        }

        config[monitorIndex] = 1;

        writeConfig(config, SLA);
    }
}