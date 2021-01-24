#include<stdio.h>
#include <stdbool.h>

int occupiedIndex = 0;
int monitorIndex = 1;
int sourceIndex = 2;
int targetIndex = 3;
int dataIndex = 4;
int responseIndex = 5;

int dataStack[3];
int dataStackLength = 0;
bool sendPermission = false;
int stationId = 2;
int selectedTarget = 3;

int main() {
    int array[6] = {1,0,0,2,3,0};
    readConfig(array);

	return 0;
}

void readConfig(int config[6]) {
    if (config[occupiedIndex] == 1) {
        sendPermission = false;
        printf("config is occupied\n");
        if (config[targetIndex] == stationId) {
            printf("config is targetted to this station\n");
            processData(config);
        }
    }
    else {
        sendPermission = true;
        printf("config is idle\n");
    }

    logConfig(config);
}

bool dataStackEmptyOrContainLagerElements(int configData) {
    if(dataStackLength == 0){
        return true;
    }

    for (int i = 0; i < dataStackLength; i++){
        if(dataStack[i] > configData){
            return true;
        }
    }
    return false;
}

void addDataToDataStack(int configData) {
    dataStack[dataStackLength] = configData;
    dataStackLength = dataStackLength + 1;
}

void processData(int config[6]){
    printf("start processing\n");
    if (dataStackEmptyOrContainLagerElements(config[dataIndex])) {
        addDataToDataStack(config[dataIndex]);
        config[responseIndex] = 1;
        printf("data accepted\n");
    } else {
        config[responseIndex] = 2;
        printf("data rejected\n");
    }
    printf("write config to slot\n");
}

void logConfig(int config[6]) {
    printf("config: ");
    for(int i = 0; i < 6; i++) {
        printf("%d, ", config[i]);
    }
    printf("\n");

    printf("sendPermission: %d\n", sendPermission);
    
    printf("dataStack: ");
    for(int i = 0; i < dataStackLength; i++) {
        printf("%d, ", dataStack[i]);
    }
    printf("\n");

    printf("dataStackLength: %d\n", dataStackLength);
}

