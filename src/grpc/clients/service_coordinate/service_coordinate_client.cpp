#include "grpc/clients/service_coordinate/service_coordinate_client.h"
#include "grpc/clients/service_coordinate/service_coordinate_client_builder.h"
#include <grpcpp/grpcpp.h>

ServiceCoordinateClient::ServiceCoordinateClient(ServiceCoordinateClientBuilder* builder) {
    std::string addr = builder->getIp() + ":" + builder->getPort();
    std::cout << "grpc client: " << addr << std::endl;
    auto channelShared = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
    stub = serviceCoordinate::Communicate::NewStub(channelShared);
}

bool ServiceCoordinateClient::informPreviousServiceInfoRequest(
        int64_t taskId, 
        std::string preserviceName,
        std::string preserviceIp, 
        std::string preservicePort,
        std::vector<std::pair<std::string, std::string>> args) {
    serviceCoordinate::InformPreviousServiceInfoRequest request;
    request.set_taskid(taskId);
    request.set_preservicename(preserviceName);
    request.set_preserviceip(preserviceIp);
    request.set_preserviceport(preservicePort);
    for (auto arg: args) {
        serviceCoordinate::InformPreviousServiceInfoRequest::Argument argument;
        argument.set_key(arg.first);
        argument.set_value(arg.second);
        request.add_args()->CopyFrom(argument);
    }
    serviceCoordinate::InformPreviousServiceInfoResponse response;
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