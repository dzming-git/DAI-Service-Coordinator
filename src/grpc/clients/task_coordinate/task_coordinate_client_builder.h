/*****************************************************************************
*  Copyright © 2023 - 2023 dzming.                                           *
*                                                                            *
*  @file     task_coordinate_client_builder.h                                *
*  @brief    the builder of task coordinate client                           *
*  @author   dzming                                                          *
*  @email    dzm_work@163.com                                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark  :                                                                 *
*****************************************************************************/
#ifndef _TASK_COORDINATE_CLIENT_BUILDER_H_
#define _TASK_COORDINATE_CLIENT_BUILDER_H_

#include "grpc/clients/task_coordinate/task_coordinate_client.h"

class TaskCoordinateClient::TaskCoordinateClientBuilder {
public:
    // 设置IP地址
    TaskCoordinateClientBuilder& setIp(const std::string& ip);

    // 设置端口号
    TaskCoordinateClientBuilder& setPort(const std::string& port);

    // 获取IP地址
    std::string getIp() const;

    // 获取端口号
    std::string getPort() const;

    // 设置最大接收字节数
    TaskCoordinateClientBuilder& setMaxReceiveBytes(int maxReceiveBytes);

    // 获取最大接收字节数
    int getMaxReceiveBytes() const;

    // 建造
    TaskCoordinateClient* build();
private:
    std::string ip;
    std::string port;
    int maxReceiveBytes;
};


#endif /* _TASK_COORDINATE_CLIENT_H_ */
