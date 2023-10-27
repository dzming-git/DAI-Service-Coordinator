/*****************************************************************************
*  Copyright © 2023 - 2023 dzming.                                           *
*                                                                            *
*  @file     service_coordinator_client.h                                        *
*  @brief    the client of task coordinator service                           *
*  @author   dzming                                                          *
*  @email    dzm_work@163.com                                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark  :  proto file: resources/protos/service_coordinator.proto             *
*****************************************************************************/
#ifndef _SERVICE_COORDINATOR_CLIENT_H_
#define _SERVICE_COORDINATOR_CLIENT_H_

#include "protos/service_coordinator/service_coordinator.grpc.pb.h"
#include "protos/service_coordinator/service_coordinator.pb.h"

class ServiceCoordinatorClient {
public:
    class ServiceCoordinatorClientBuilder;
    bool informPreviousServiceInfoRequest(
            int64_t taskId, 
            std::string preserviceName,
            std::string preserviceIp, 
            std::string preservicePort, 
            std::vector<std::pair<std::string, std::string>> args);
private:
    ServiceCoordinatorClient(ServiceCoordinatorClientBuilder* builder);
    std::unique_ptr<serviceCoordinator::Communicate::Stub> stub;
};

#endif /* _SERVICE_COORDINATOR_CLIENT_H_ */
