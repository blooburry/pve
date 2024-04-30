
#include "MqttService.h"

MqttService::MqttService() {
    mosquitto_lib_init();
    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        std::cerr << "Error: Unable to initialize Mosquitto library\n";
        exit(EXIT_FAILURE);
    }
    connectToBroker();
}

MqttService::~MqttService() {
    disconnectFromBroker();
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}

void MqttService::connectToBroker() {
    if (mosquitto_connect(mosq, brokerAddress.c_str(), brokerPort, 0) != MOSQ_ERR_SUCCESS) {
        std::cerr << "Error: Unable to connect to MQTT broker\n";
        exit(EXIT_FAILURE);
    }
}

void MqttService::disconnectFromBroker() {
    mosquitto_disconnect(mosq);
}

void MqttService::publishData(const std::string& topic, float data) {
    std::string fullTopic = "/" + topic;
    int ret = mosquitto_publish(mosq, NULL, fullTopic.c_str(), sizeof(float), &data, 0, false);
    if (ret != MOSQ_ERR_SUCCESS) {
        std::cerr << "Error: Failed to publish data on topic " << fullTopic << "\n";
    }
}

void MqttService::sendMagData(float magData) {
    publishData("imu/mag", magData);
}

void MqttService::sendAccData(float accData) {
    publishData("imu/acc", accData);
}

void MqttService::sendGyroData(float gyroData) {
    publishData("imu/gyro", gyroData);
}