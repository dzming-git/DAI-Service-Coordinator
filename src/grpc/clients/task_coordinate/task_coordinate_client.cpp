#include "grpc/clients/task_coordinate/task_coordinate_client.h"
#include "grpc/clients/task_coordinate/task_coordinate_client_builder.h"
#include <grpcpp/grpcpp.h>

TaskCoordinateClient::TaskCoordinateClient(TaskCoordinateClientBuilder* builder) {
    std::string addr = builder->getIp() + ":" + builder->getPort();
    std::cout << "grpc client: " << addr << std::endl;
    auto channelShared = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
    stub = taskCoordinate::Communicate::NewStub(channelShared);
}

bool TaskCoordinateClient::informPreviousServiceInfoRequest(
        int64_t taskId, 
        std::string preserviceName,
        std::string preserviceIp, 
        std::string preservicePort,
        std::vector<std::pair<std::string, std::string>> args) {
    taskCoordinate::InformPreviousServiceInfoRequest request;
    request.set_taskid(taskId);
    request.set_preservicename(preserviceName);
    request.set_preserviceip(preserviceIp);
    request.set_preserviceport(preservicePort);
    for (auto arg: args) {
        taskCoordinate::InformPreviousServiceInfoRequest::Argument argument;
        argument.set_key(arg.first);
        argument.set_value(arg.second);
        request.add_args()->CopyFrom(argument);
    }
    taskCoordinate::InformPreviousServiceInfoResponse response;
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