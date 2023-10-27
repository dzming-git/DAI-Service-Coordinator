# CMake最低版本
cmake_minimum_required(VERSION 3.10)

# 项目名 语言
project(service_coordinator C CXX)

# C++版本
set(CMAKE_CXX_STANDARD 20)

# 可执行程序的输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 生成文件的输出目录
set(GENERATED_OUT_PATH ${PROJECT_SOURCE_DIR}/generated)

#查找本地Protobuf模块的库信息，实际上CMake就是在找Protobuf-config.cmake文件
set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
if(CMAKE_CROSSCOMPILING)
  find_program(_PROTOBUF_PROTOC protoc)
else()
  set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif()

# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
#查找本地gRPC模块的库信息
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
if(CMAKE_CROSSCOMPILING)
  find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
  set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()


# proto文件生成代码文件

## 设置生成文件路径

set(protos service_coordinator)
foreach(proto ${protos})
    message("current generating: ${proto}")
    set(data_proto ${PROJECT_SOURCE_DIR}/resources/protos/${proto}.proto)
    set(data_proto_srcs "${GENERATED_OUT_PATH}/protos/${proto}/${proto}.pb.cc")
    set(data_proto_hdrs "${GENERATED_OUT_PATH}/protos/${proto}/${proto}.pb.h")
    set(data_grpc_srcs "${GENERATED_OUT_PATH}/protos/${proto}/${proto}.grpc.pb.cc")
    set(data_grpc_hdrs "${GENERATED_OUT_PATH}/protos/${proto}/${proto}.grpc.pb.h")

    ## 生成文件
    add_custom_command(
        OUTPUT "${data_proto_srcs}" "${data_proto_hdrs}" "${data_grpc_srcs}" "${data_grpc_hdrs}"
        COMMAND protoc
        ARGS --grpc_out "${GENERATED_OUT_PATH}/protos/${proto}"
            --cpp_out "${GENERATED_OUT_PATH}/protos/${proto}"
            -I "${PROJECT_SOURCE_DIR}/resources/protos"
            --plugin=protoc-gen-grpc=`which grpc_cpp_plugin`
            "${data_proto}"
        DEPENDS "${data_proto}")

    #将grpc的四个文件编译成一个库
    # data_grpc_proto
    add_library(${proto}_data_grpc_proto
    ${data_grpc_srcs}
    ${data_grpc_hdrs}
    ${data_proto_srcs}
    ${data_proto_hdrs})
    #链接库data_grpc_proto，会生成链接文件
    target_link_libraries(${proto}_data_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})
endforeach()


# libhv
set(HV_LIBRARY /usr/local/lib/libhv.so)

# include
include_directories("${GENERATED_OUT_PATH}")
include_directories("${PROJECT_SOURCE_DIR}/src")

set(HEADERS
    src/consul/consul_client.h
    src/consul/service_info.h
    src/grpc/clients/service_coordinator/service_coordinator_client.h
    src/grpc/clients/service_coordinator/service_coordinator_client_builder.h
    )

set(SOURCES
    main.cpp
    src/consul/consul_client.cpp
    src/consul/service_info.cpp
    src/grpc/clients/service_coordinator/service_coordinator_client.cpp
    src/grpc/clients/service_coordinator/service_coordinator_client_builder.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# local
set(LOCAL_INCLUDE_DIRS "/usr/local/include")
target_include_directories(${PROJECT_NAME} PRIVATE ${HV_INCLUDE_DIRS})

# OpenCV
target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

# HCNetSDK
target_include_directories(${PROJECT_NAME} PRIVATE ${HCNetSDK_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${HCNetSDK_LIBS})

# proto
foreach(proto ${protos})
    target_link_libraries(${PROJECT_NAME}
        ${proto}_data_grpc_proto
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})
endforeach()

# linhv
target_link_libraries(${PROJECT_NAME} ${HV_LIBRARY})
