cmake_minimum_required(VERSION 3.20)

project(rbx_physics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ─────────────────────────────────────────────────────────────────────────
# Include roots
# ─────────────────────────────────────────────────────────────────────────
set(APP_ROOT    "${CMAKE_CURRENT_SOURCE_DIR}/App")
set(APP_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/App/include")
set(G3D_ROOT    "${CMAKE_CURRENT_SOURCE_DIR}/Rendering/g3d")

message(STATUS "APP_ROOT    = ${APP_ROOT}")
message(STATUS "APP_INCLUDE = ${APP_INCLUDE}")
message(STATUS "G3D_ROOT    = ${G3D_ROOT}")

if(MSVC)
    add_compile_options(
        /W4
        /permissive
        /wd4244
        /wd4458
        /wd4100
        /wd4239
        /wd4189
        /wd4305
        /wd4706
        /wd4390
        /wd4456
    )
else()
    add_compile_options(-Wall -Wextra)
endif()

# ─────────────────────────────────────────────────────────────────────────
# Shim include paths (G3D + fake Boost + winwrap.h)
# ─────────────────────────────────────────────────────────────────────────
add_library(rbx_g3d INTERFACE)
target_include_directories(rbx_g3d INTERFACE
    "${APP_INCLUDE}"
    "${APP_ROOT}"
    "${G3D_ROOT}"
)

target_compile_definitions(rbx_g3d INTERFACE
    BOOST_ALL_NO_LIB
    _CRT_SECURE_NO_WARNINGS
    _SCL_SECURE_NO_WARNINGS
    _HAS_AUTO_PTR_ETC=1
)

# ─────────────────────────────────────────────────────────────────────────
# Engine sources
# ─────────────────────────────────────────────────────────────────────────
set(RBX_ENGINE_SOURCES
    # v8kernel
    ${APP_ROOT}/v8kernel/Constants.cpp
    ${APP_ROOT}/v8kernel/Kernel.cpp
    ${APP_ROOT}/v8kernel/Body.cpp
    ${APP_ROOT}/v8kernel/SimBody.cpp
    ${APP_ROOT}/v8kernel/Cofm.cpp
    ${APP_ROOT}/v8kernel/Point.cpp
    ${APP_ROOT}/v8kernel/Connector.cpp
    ${APP_ROOT}/v8kernel/Link.cpp
    ${APP_ROOT}/v8kernel/Pair.cpp

    # v8world — geometry
    ${APP_ROOT}/v8world/Block.cpp
    ${APP_ROOT}/v8world/Ball.cpp
    ${APP_ROOT}/v8world/Edge.cpp
    ${APP_ROOT}/v8world/Joint.cpp
    ${APP_ROOT}/v8world/RigidJoint.cpp
    ${APP_ROOT}/v8world/Primitive.cpp

    # v8world — grouping
    ${APP_ROOT}/v8world/Assembly.cpp
    ${APP_ROOT}/v8world/Clump.cpp
    ${APP_ROOT}/v8world/Mechanism.cpp
    ${APP_ROOT}/v8world/IMoving.cpp

    # v8world — pipeline base
    ${APP_ROOT}/v8world/IPipelined.cpp
    ${APP_ROOT}/v8world/IWorldStage.cpp
    ${APP_ROOT}/v8world/SpatialHash.cpp
    ${APP_ROOT}/v8world/ContactManager.cpp
    ${APP_ROOT}/v8world/Contact.cpp

    # v8world — stages
    ${APP_ROOT}/v8world/JointStage.cpp
    ${APP_ROOT}/v8world/ClumpStage.cpp
    ${APP_ROOT}/v8world/AssemblyStage.cpp
    ${APP_ROOT}/v8world/CollisionStage.cpp
    ${APP_ROOT}/v8world/SleepStage.cpp
    ${APP_ROOT}/v8world/SeparateStage.cpp
    ${APP_ROOT}/v8world/SimJobStage.cpp

    # v8world — joints
    ${APP_ROOT}/v8world/MutilJoint.cpp
    ${APP_ROOT}/v8world/MotorJoint.cpp
    ${APP_ROOT}/v8world/RotateJoint.cpp
    ${APP_ROOT}/v8world/GlueJoint.cpp
    ${APP_ROOT}/v8world/SnapJoint.cpp
    ${APP_ROOT}/v8world/WeldJoint.cpp
    ${APP_ROOT}/v8world/JointBuilder.cpp
    ${APP_ROOT}/v8world/World.cpp

    # util
    ${APP_ROOT}/util/NormalId.cpp
    ${APP_ROOT}/util/Math.cpp
    ${APP_ROOT}/util/Face.cpp
    ${APP_ROOT}/util/Extents.cpp
    ${APP_ROOT}/util/Quaternion.cpp
    ${APP_ROOT}/util/Profiling.cpp
    ${APP_ROOT}/util/Debug.cpp
    ${APP_ROOT}/util/Units.cpp
    ${APP_ROOT}/util/RunningAverage.cpp
    ${APP_ROOT}/util/Guid.cpp
    ${APP_ROOT}/util/Name.cpp
    ${APP_ROOT}/util/standardout.cpp
    ${APP_ROOT}/util/Log.cpp
)

add_library(rbx_engine STATIC ${RBX_ENGINE_SOURCES})
target_link_libraries(rbx_engine PUBLIC rbx_g3d)

if(MSVC)
    target_compile_options(rbx_engine PRIVATE /FI"${G3D_ROOT}/winwrap.h")
    target_link_libraries(rbx_engine PUBLIC ole32 oleaut32)
endif()