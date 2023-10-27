#include "grpc/clients/service_coordinator/service_coordinator_client_builder.h"

ServiceCoordinatorClient::ServiceCoordinatorClientBuilder& ServiceCoordinatorClient::ServiceCoordinatorClientBuilder::setIp(const std::string& ip) {
    this->ip = ip;
    return *this;
}

ServiceCoordinatorClient::ServiceCoordinatorClientBuilder& ServiceCoordinatorClient::ServiceCoordinatorClientBuilder::setPort(const std::string& port) {
    this->port = port;
    return *this;
}

std::string ServiceCoordinatorClient::ServiceCoordinatorClientBuilder::getIp() const {
    return ip;
}

std::string ServiceCoordinatorClient::ServiceCoordinatorClientBuilder::getPort() const {
    return port;
}

ServiceCoordinatorClient::ServiceCoordinatorClientBuilder& ServiceCoordinatorClient::ServiceCoordinatorClientBuilder::setMaxReceiveBytes(int maxReceiveBytes) {
    this->maxReceiveBytes = maxReceiveBytes;
    return *this;
}

int ServiceCoordinatorClient::ServiceCoordinatorClientBuilder::getMaxReceiveBytes() const {
    return maxReceiveBytes;
}

ServiceCoordinatorClient * ServiceCoordinatorClient::ServiceCoordinatorClientBuilder::build() {
    return new ServiceCoordinatorClient(this);
}
