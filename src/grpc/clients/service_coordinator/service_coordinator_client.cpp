#include "grpc/clients/service_coordinator/service_coordinator_client.h"
#include "grpc/clients/service_coordinator/service_coordinator_client_builder.h"
#include <grpcpp/grpcpp.h>

ServiceCoordinatorClient::ServiceCoordinatorClient(ServiceCoordinatorClientBuilder* builder) {
    std::string addr = builder->getIp() + ":" + builder->getPort();
    std::cout << "grpc client: " << addr << std::endl;
    auto channelShared = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
    stub = serviceCoordinator::Communicate::NewStub(channelShared);
}

bool ServiceCoordinatorClient::informPreviousServiceInfoRequest(
        int64_t taskId, 
        std::string preserviceName,
        std::string preserviceIp, 
        std::string preservicePort,
        std::vector<std::pair<std::string, std::string>> args) {
    serviceCoordinator::InformPreviousServiceInfoRequest request;
    request.set_taskid(taskId);
    request.set_preservicename(preserviceName);
    request.set_preserviceip(preserviceIp);
    request.set_preserviceport(preservicePort);
    for (auto arg: args) {
        serviceCoordinator::InformPreviousServiceInfoRequest::Argument argument;
        argument.set_key(arg.first);
        argument.set_value(arg.second);
        request.add_args()->CopyFrom(argument);
    }
    serviceCoordinator::InformPreviousServiceInfoResponse response;
    grpc::ClientContext context;
    auto status = stub->informPreviousServiceInfo(&context, request, &response);
    if (status.ok()) {
        int32_t responseCode = response.response().code();
        std::string responseMessage = response.response().message();
        if (!responseMessage.empty()) {
            std::cout << responseMessage << std::endl;
        }
        if (200 == responseCode) {
            return true;
        }
    }
    return false;
}