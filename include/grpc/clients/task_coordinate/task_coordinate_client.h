/*****************************************************************************
*  Copyright © 2023 - 2023 dzming.                                           *
*                                                                            *
*  @file     task_coordinate_client.h                                        *
*  @brief    the client of task coordinate service                           *
*  @author   dzming                                                          *
*  @email    dzm_work@163.com                                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark  :  proto file: resources/protos/task_coordinate.proto             *
*****************************************************************************/
#ifndef _TASK_COORDINATE_CLIENT_H_
#define _TASK_COORDINATE_CLIENT_H_

#include "protos/task_coordinate/task_coordinate.grpc.pb.h"
#include "protos/task_coordinate/task_coordinate.pb.h"

class TaskCoordinateClient {
public:
    class TaskCoordinateClientBuilder;
    bool informPreviousServiceInfoRequest(
            int64_t taskId, 
            std::string preserviceIp, 
            std::string preservicePort, 
            std::vector<std::pair<std::string, std::string>> args);
private:
    TaskCoordinateClient(TaskCoordinateClientBuilder* builder);
    std::unique_ptr<taskCoordinate::Communicate::Stub> stub;
};

#endif /* _TASK_COORDINATE_CLIENT_H_ */
