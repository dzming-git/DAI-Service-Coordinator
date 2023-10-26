/*****************************************************************************
*  Copyright © 2023 - 2023 dzming.                                           *
*                                                                            *
*  @file     service_coordinate_client_builder.h                                *
*  @brief    the builder of task coordinate client                           *
*  @author   dzming                                                          *
*  @email    dzm_work@163.com                                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark  :                                                                 *
*****************************************************************************/
#ifndef _SERVICE_COORDINATE_CLIENT_BUILDER_H_
#define _SERVICE_COORDINATE_CLIENT_BUILDER_H_

#include "grpc/clients/service_coordinate/service_coordinate_client.h"

class ServiceCoordinateClient::ServiceCoordinateClientBuilder {
public:
    // 设置IP地址
    ServiceCoordinateClientBuilder& setIp(const std::string& ip);

    // 设置端口号
    ServiceCoordinateClientBuilder& setPort(const std::string& port);

    // 获取IP地址
    std::string getIp() const;

    // 获取端口号
    std::string getPort() const;

    // 设置最大接收字节数
    ServiceCoordinateClientBuilder& setMaxReceiveBytes(int maxReceiveBytes);

    // 获取最大接收字节数
    int getMaxReceiveBytes() const;

    // 建造
    ServiceCoordinateClient* build();
private:
    std::string ip;
    std::string port;
    int maxReceiveBytes;
};


#endif /* _SERVICE_COORDINATE_CLIENT_H_ */
