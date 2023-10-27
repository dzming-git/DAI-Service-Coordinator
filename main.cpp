#include "grpc/clients/service_coordinator/service_coordinator_client_builder.h"
#include <vector>
#include "consul/consul_client.h"
#include <unordered_map>

struct ServiceNode {
    std::string serviceIp;
    std::string servicePort;
    std::string serviceName;
};

struct ServiceNodeConnection {
    int64_t taskId;
    ServiceNode* preNode;
    ServiceNode* curNode;
    std::vector<std::pair<std::string, std::string>> args;
};

void test1() {
    int64_t taskId = 123457;
    std::string imageHarmonyIp = "172.18.0.3";
    std::string imageHarmonyName = "image harmony";
    std::vector<std::pair<std::string, std::string>> args;
    args.emplace_back("ImgType", "hikvision");
    args.emplace_back("DeviceAddress", "192.168.1.7");
    args.emplace_back("UserName", "admin");
    args.emplace_back("Password", "Scu50501");
    args.emplace_back("Port", "8000");
    ServiceCoordinatorClient::ServiceCoordinatorClientBuilder serviceCoordinatorClientBuilder;
    auto serviceCoordinatorClient = serviceCoordinatorClientBuilder
        .setIp("172.18.0.9")
        .setPort("5000")
        .build();
    serviceCoordinatorClient->informPreviousServiceInfoRequest(taskId, imageHarmonyName, imageHarmonyIp, "5000", args);
}

void test2() {
    int64_t taskId = 12345; // 模拟
    std::unordered_map<std::string, ServiceNode*> ServiceNodeMap;
    std::vector<ServiceNodeConnection*> serviceConnections;
 
    ServiceNode imageHarmonyNode;
    imageHarmonyNode.serviceName = "image harmony";
    ServiceNodeMap.emplace(imageHarmonyNode.serviceName, &imageHarmonyNode);

    ServiceNode targetDetectionNode;
    targetDetectionNode.serviceName = "target detection";
    ServiceNodeMap.emplace(targetDetectionNode.serviceName, &targetDetectionNode);

    ServiceNodeConnection connectImageHarmony2TargetDetection;
    connectImageHarmony2TargetDetection.preNode = &imageHarmonyNode;
    connectImageHarmony2TargetDetection.curNode = &targetDetectionNode;
    connectImageHarmony2TargetDetection.taskId = taskId;
    connectImageHarmony2TargetDetection.args.emplace_back("ImgType", "hikvision");
    connectImageHarmony2TargetDetection.args.emplace_back("DeviceAddress", "192.168.1.16");
    connectImageHarmony2TargetDetection.args.emplace_back("UserName", "admin");
    connectImageHarmony2TargetDetection.args.emplace_back("Password", "Scu50501");
    connectImageHarmony2TargetDetection.args.emplace_back("Port", "8000");
    serviceConnections.emplace_back(&connectImageHarmony2TargetDetection);

    ConsulClient consul;
    for (auto& node : ServiceNodeMap) {
        std::vector<ServiceInfo> services;
        consul.discoverServices(node.second->serviceName, services);
        if (!services.empty()) {
            auto info = services[rand() % services.size()];
            node.second->serviceIp = info.getServiceIp();
            node.second->servicePort = info.getServicePort();
        }
    }


    ServiceCoordinatorClient::ServiceCoordinatorClientBuilder serviceCoordinatorClientBuilder;
    for (const auto& connection : serviceConnections) {
        auto serviceCoordinatorClient = serviceCoordinatorClientBuilder
            .setIp(connection->curNode->serviceIp)
            .setPort(connection->curNode->servicePort)
            .build();
        serviceCoordinatorClient->informPreviousServiceInfoRequest(
            taskId, 
            connection->preNode->serviceName, 
            connection->preNode->serviceIp,
            connection->preNode->servicePort, 
            connection->args);
    }
}

int main(int argc, char** argv) {
    test2();
    return 0;
}
