/*****************************************************************************
*  Copyright © 2023 - 2023 dzming.                                           *
*                                                                            *
*  @file     consul_client.h                                                 *
*  @brief    Consul Client                                                   *
*  @author   dzming                                                          *
*  @email    dzm_work@163.com                                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark  :                                                                 *
*****************************************************************************/

#ifndef _CONSUL_CLIENT_H_
#define _CONSUL_CLIENT_H_

#include <vector>
#include <unordered_map>
#include <string>
#include <chrono>
#include <mutex>
#include "consul/server_info.h"

class ConsulClient {
public:
    ConsulClient();
    // ~ConsulClient();
    ConsulClient& setConsulAddress(std::string);
    ConsulClient& setConsulPort(std::string);

    bool registerService(const ServerInfo& serverInfo);
    // bool deregisterService();

    struct TagRequirement;
    bool discoverServices(std::string serviceName, std::vector<TagRequirement> tags, std::vector<ServerInfo>& services);
private:
    std::string consulAddress;
    std::string consulPort;
};

struct ConsulClient::TagRequirement {
    enum Requirement {
        MUST,  // 每个服务都必有的
        COMB,  // 不一定每个服务有，但可以通过服务进行组合
        PRIOR  // 可以没有，优先
    };
    std::string tag;
    Requirement requirement;
};

#endif /* _CONSUL_CLIENT_H_ */
