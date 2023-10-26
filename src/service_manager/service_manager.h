/*****************************************************************************
*  Copyright © 2023 - 2023 dzming.                                           *
*                                                                            *
*  @file     service_manager.h                                               *
*  @brief    Manage service nodes and their connection relationships         *
*  @author   dzming                                                          *
*  @email    dzm_work@163.com                                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark  :                                                                 *
*****************************************************************************/

#ifndef _SERVICE_MANAGER_H_
#define _SERVICE_MANAGER_H_

#include <vector>
#include <string>
#include <mutex>
#include <unordered_map>
#include "consul/service_info.h"

class ServiceManager {
public:
    static ServiceManager* getSingletonInstance();
    struct TaskInfo;    
    struct TagRequirement;

    int64_t creatTask();
    bool addServicesConnection(
        int64_t taskId, 
        std::string preServiceName,  // 前置服务
        std::string curServiceName,
        std::vector<TagRequirement> preServiceTags,
        std::vector<std::pair<std::string, std::string>> args);
private:
    ServiceManager();
    ~ServiceManager();

    static ServiceManager* instance;
    static pthread_mutex_t lock;

    std::unordered_map<int64_t /* task ID */, TaskInfo*> taskInfoMap;
};

struct ServiceManager::TaskInfo {
    ~TaskInfo();
    struct ServiceConnection;
    int64_t taskId;
    std::unordered_map<std::string /* service name */, ServiceInfo*> serviceInfoMap;
    std::vector<ServiceConnection*> serviceConnections;
};

struct ServiceManager::TaskInfo::ServiceConnection {
    ServiceInfo* preService;
    ServiceInfo* curService;
    std::vector<TagRequirement> preServiceTags;
    std::vector<std::pair<std::string, std::string>> args;
};

struct ServiceManager::TagRequirement {
    enum Requirement {
        MUST,  // 每个服务都必有的
        COMB,  // 不一定每个服务有，但可以通过服务进行组合
        PRIOR  // 可以没有，优先
    };
    TagRequirement(std::string, Requirement);
    std::string tag;
    Requirement requirement;
};

#endif /* _SERVICE_MANAGER_H_ */
