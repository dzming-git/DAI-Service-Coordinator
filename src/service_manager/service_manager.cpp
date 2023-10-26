#include "service_manager/service_manager.h"

ServiceManager::ServiceManager() {

}

ServiceManager::~ServiceManager() {
    for (auto& taskInfo : taskInfoMap) {
        delete taskInfo.second;
    }
}

ServiceManager::TaskInfo::~TaskInfo() {
    for (auto& connect : serviceConnections) {
        delete connect;
    }
}


ServiceManager::TagRequirement::TagRequirement(std::string tag, Requirement requirement):
tag(tag), requirement(requirement) {
}

ServiceManager * ServiceManager::getSingletonInstance() {
	if (nullptr == instance) {
		pthread_mutex_lock(&lock);
		if (nullptr == instance) {
			instance = new ServiceManager();
		}
        pthread_mutex_unlock(&lock);
	}
	return instance;
}
