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

int main() {
    testSend();
    // testRead();

	return 0;
}

void readConfig(int config[6]) {
    if (config[occupiedIndex] == 1) {
        sendPermission = false;
        printf("config is occupied");
        if (config[targetIndex] == stationId) {
            printf(" and targetted to this station\n");
            processData(config);
        } else {
            printf(" but not targetted to this station\n");
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

int takeDataFromDataStack() {
    int dataToSend = dataStack[dataStackLength - 1];
    dataStack[dataStackLength - 1] = 0;
    dataStackLength = dataStackLength - 1;
    return dataToSend;
}

int getTargetAddress() {
    return 3;
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
    printf("\n");
    printf("config: ");
    printArray(config, 6);
    printf("\n");
    logLite();
}

void logLite() {
    printf("sendPermission: %d\n", sendPermission);
    printf("dataStackLength: %d\n", dataStackLength);
    
    printf("dataStack: ");
    printArray(dataStack, dataStackLength);
    printf("\n\n");
}

void printArray(int *arrayReference, int length) {
    for(int i = 0; i < length; i++) {
        printf("%d, ", arrayReference[i]);
    }
}

void onButtonSendEvent() {
    printf("handling send button press event\n");
    if (dataStackLength != 0 && sendPermission) {
        printf("take last item of dataStack and build config\n");
        int dataToSend = takeDataFromDataStack();
        int targetToSend = getTargetAddress();
        int config[6] = { 1, 0, stationId, targetToSend, dataToSend, 3 };
        sendPermission = false;

        printf("write config to slot\n");
        logConfig(config);
    }
}

void testSend() {
    //sendPermission = false; dataStackLength = 0; // not writing to slot because dataStackLength == 0 or sendPermission == false
    //sendPermission = true; dataStackLength = 0; // not writing to slot because dataStackLength == 0 or sendPermission == false
    //sendPermission = false; dataStackLength = 1; // not writing to slot because dataStackLength == 0 or sendPermission == false
    sendPermission = true; dataStackLength = 1; // writing to slot because dataStackLength != 0 and sendPermission == true

    logLite();
    onButtonSendEvent();
}

void testRead() {
    //int array[6] = {1,0,0,3,3,0}; // occupied, but not targetted to this station

    int array[6] = {1,0,0,2,3,0}; // occupied and targetted to this station - data accepted, because dataStackLength = 0

    //dataStack[0] = 4;
    //dataStack[1] = 0;
    //dataStack[2] = 0;
    //dataStackLength = 1;
    //int array[6] = {1,0,0,2,3,0}; // occupied and targetted to this station - data accepted, because data is smaller then dataStackEntry (3 < 4)
    //int array[6] = {1,0,0,2,5,0}; // occupied and targetted to this station - data rejected, because data is bigger then dataStackEntry (5 > 4)

    logConfig(array);
    printf("\n");
    readConfig(array);
}

