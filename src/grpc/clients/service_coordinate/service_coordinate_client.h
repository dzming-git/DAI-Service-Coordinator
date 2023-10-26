/*****************************************************************************
*  Copyright © 2023 - 2023 dzming.                                           *
*                                                                            *
*  @file     service_coordinate_client.h                                        *
*  @brief    the client of task coordinate service                           *
*  @author   dzming                                                          *
*  @email    dzm_work@163.com                                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark  :  proto file: resources/protos/service_coordinate.proto             *
*****************************************************************************/
#ifndef _SERVICE_COORDINATE_CLIENT_H_
#define _SERVICE_COORDINATE_CLIENT_H_

#include "protos/service_coordinate/service_coordinate.grpc.pb.h"
#include "protos/service_coordinate/service_coordinate.pb.h"

class ServiceCoordinateClient {
public:
    class ServiceCoordinateClientBuilder;
    bool informPreviousServiceInfoRequest(
            int64_t taskId, 
            std::string preserviceName,
            std::string preserviceIp, 
            std::string preservicePort, 
            std::vector<std::pair<std::string, std::string>> args);
private:
    ServiceCoordinateClient(ServiceCoordinateClientBuilder* builder);
    std::unique_ptr<serviceCoordinate::Communicate::Stub> stub;
};

#endif /* _SERVICE_COORDINATE_CLIENT_H_ */
