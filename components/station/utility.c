bool checkI2CConnection(int SLA)
{
    // check if SLA is available in i2c bus
    return true;
}

void writeConfig(int config[6], int SLA)
{
    send_start();
    start_write(SLA);
    send_byte(config[0]);
    send_byte(config[1]);
    send_byte(config[2]);
    send_byte(config[3]);
    send_byte(config[4]);
    send_byte(config[5]);
    send_stop();
}

void readConfig(int config[6], int SLA)
{
    send_start();
    start_read(SLA);
    config[0] = read_ack();
    config[1] = read_ack();
    config[2] = read_ack();
    config[3] = read_ack();
    config[4] = read_ack();
    config[5] = read_nack();
    send_stop();
}

int checkPin(int pinNr)
{
    return 0;
}