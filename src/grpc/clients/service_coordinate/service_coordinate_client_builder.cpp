#include "grpc/clients/service_coordinate/service_coordinate_client_builder.h"

ServiceCoordinateClient::ServiceCoordinateClientBuilder& ServiceCoordinateClient::ServiceCoordinateClientBuilder::setIp(const std::string& ip) {
    this->ip = ip;
    return *this;
}

ServiceCoordinateClient::ServiceCoordinateClientBuilder& ServiceCoordinateClient::ServiceCoordinateClientBuilder::setPort(const std::string& port) {
    this->port = port;
    return *this;
}

std::string ServiceCoordinateClient::ServiceCoordinateClientBuilder::getIp() const {
    return ip;
}

std::string ServiceCoordinateClient::ServiceCoordinateClientBuilder::getPort() const {
    return port;
}

ServiceCoordinateClient::ServiceCoordinateClientBuilder& ServiceCoordinateClient::ServiceCoordinateClientBuilder::setMaxReceiveBytes(int maxReceiveBytes) {
    this->maxReceiveBytes = maxReceiveBytes;
    return *this;
}

int ServiceCoordinateClient::ServiceCoordinateClientBuilder::getMaxReceiveBytes() const {
    return maxReceiveBytes;
}

ServiceCoordinateClient * ServiceCoordinateClient::ServiceCoordinateClientBuilder::build() {
    return new ServiceCoordinateClient(this);
}
