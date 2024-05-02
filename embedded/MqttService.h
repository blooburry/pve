#ifndef MQTT_SERVICE_H
#define MQTT_SERVICE_H

#include <iostream>
#include <string>
#include <mosquitto.h>

class MqttService {
public:
    MqttService();
    ~MqttService();

    void sendMagData(float magData);
    void sendAccData(float accData);
    void sendGyroData(float gyroData);
    void sendLijnData(float lijnData);

private:
    std::string brokerAddress = "localhost";
    int brokerPort = 1883;
    struct mosquitto *mosq;

    void connectToBroker();
    void disconnectFromBroker();
    void publishData(const std::string& topic, float data);
};

#endif
