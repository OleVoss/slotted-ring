
occupiedIndex = 0
sourceIndex = 2
targetIndex = 3
dataIndex = 4
responseIndex = 5

dataStack = [4]
stationId = 2
selectedTarget = 3
sendPermission = False

def readConfig(config):
    if config[occupiedIndex] == 1:
        sendPermission = False
        print('config is occupied')
        if config[targetIndex] == stationId:
            print('config is targetted to this station')
            processData(config)
    else:
        sendPermission = True
        print('config is idle')

    print('config', config)
    print('dataStack', dataStack)
    print('sendPermission', sendPermission)

def processData(config):
    print('start processing')
    if dataStack and max(dataStack) > config[dataIndex]:
        dataStack.append(config[dataIndex])
        config[responseIndex] = 1
        print('data accepted')
    else:
        config[responseIndex] = 2
        print('data rejected')
    writeConfig(config)

def writeConfig(config):
    print('write config to slot')


def onButtonSendEvent():
    print('Handling send button press event')
    if dataStack and sendPermission:
        print('Take last item of dataStack and build config')
        data = dataStack.pop()
        config = [1,0,stationId,selectedTarget,data,3]
        sendPermission = False
        writeConfig(config)

        print('config', config)
        print('dataStack', dataStack)
        print('sendPermission', sendPermission)


# should be idle and wont be processed // config: [0, 0, 1, 1, 5, 3] / dataStack: [4] / sendPermission: true
readConfig([0,0,1,1,5,3])

# should be occupied but wont be processed // config: [1, 0, 1, 1, 5, 3] / dataStack: [4] / sendPermission: false
readConfig([1,0,1,1,5,3])

# should get processed and rejected // config: [1, 0, 1, 2, 5, 2] / dataStack [4] / sendPermission: false
readConfig([1,0,1,2,5,3])

# should get processed and accepted // config: [1, 0, 1, 2, 3, 1] / dataStack [4, 3] / sendPermission: false
readConfig([1,0,1,2,3,3])



# TODO: onButtonSendEvent() überprüfen 
# - hier habe ich noch Probleme mit dem Setzen und Lesen globaler Variablen (zumindest mit bool sendPermission)

# def setGlobalSendPermission(sendPermissionValue, dataStackValue):
#     global sendPermission
#     sendPermission = sendPermissionValue
#     global dataStack
#     dataStack = dataStackValue

# shouldnt be sent
# setGlobalSendPermission(False, [])
# onButtonSendEvent()
# print(sendPermission)
# print(dataStack)

# shouldnt be sent
# setGlobalSendPermission(True, [])
# onButtonSendEvent()
# print(sendPermission)
# print(dataStack)

# shouldnt be sent
# setGlobalSendPermission(False, [4])
# onButtonSendEvent()
# print(sendPermission)
# print(dataStack)