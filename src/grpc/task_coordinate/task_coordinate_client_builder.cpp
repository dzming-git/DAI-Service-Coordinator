#include "grpc/clients/task_coordinate/task_coordinate_client_builder.h"

TaskCoordinateClient::TaskCoordinateClientBuilder& TaskCoordinateClient::TaskCoordinateClientBuilder::setIp(const std::string& ip) {
    this->ip = ip;
    return *this;
}

TaskCoordinateClient::TaskCoordinateClientBuilder& TaskCoordinateClient::TaskCoordinateClientBuilder::setPort(const std::string& port) {
    this->port = port;
    return *this;
}

std::string TaskCoordinateClient::TaskCoordinateClientBuilder::getIp() const {
    return ip;
}

std::string TaskCoordinateClient::TaskCoordinateClientBuilder::getPort() const {
    return port;
}

TaskCoordinateClient::TaskCoordinateClientBuilder& TaskCoordinateClient::TaskCoordinateClientBuilder::setMaxReceiveBytes(int maxReceiveBytes) {
    this->maxReceiveBytes = maxReceiveBytes;
    return *this;
}

int TaskCoordinateClient::TaskCoordinateClientBuilder::getMaxReceiveBytes() const {
    return maxReceiveBytes;
}

TaskCoordinateClient * TaskCoordinateClient::TaskCoordinateClientBuilder::build() {
    return new TaskCoordinateClient(this);
}
