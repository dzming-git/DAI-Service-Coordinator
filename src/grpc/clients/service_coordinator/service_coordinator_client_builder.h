/*****************************************************************************
*  Copyright © 2023 - 2023 dzming.                                           *
*                                                                            *
*  @file     service_coordinator_client_builder.h                                *
*  @brief    the builder of task coordinator client                           *
*  @author   dzming                                                          *
*  @email    dzm_work@163.com                                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark  :                                                                 *
*****************************************************************************/
#ifndef _SERVICE_COORDINATOR_CLIENT_BUILDER_H_
#define _SERVICE_COORDINATOR_CLIENT_BUILDER_H_

#include "grpc/clients/service_coordinator/service_coordinator_client.h"

class ServiceCoordinatorClient::ServiceCoordinatorClientBuilder {
public:
    // 设置IP地址
    ServiceCoordinatorClientBuilder& setIp(const std::string& ip);

    // 设置端口号
    ServiceCoordinatorClientBuilder& setPort(const std::string& port);

    // 获取IP地址
    std::string getIp() const;

    // 获取端口号
    std::string getPort() const;

    // 设置最大接收字节数
    ServiceCoordinatorClientBuilder& setMaxReceiveBytes(int maxReceiveBytes);

    // 获取最大接收字节数
    int getMaxReceiveBytes() const;

    // 建造
    ServiceCoordinatorClient* build();
private:
    std::string ip;
    std::string port;
    int maxReceiveBytes;
};


#endif /* _SERVICE_COORDINATOR_CLIENT_H_ */
