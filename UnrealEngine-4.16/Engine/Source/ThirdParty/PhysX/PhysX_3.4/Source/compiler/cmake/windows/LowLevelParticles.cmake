#
# Build LowLevelParticles
#

SET(PHYSX_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../../../)

SET(LL_SOURCE_DIR ${PHYSX_SOURCE_DIR}/LowLevelParticles/src)

FIND_PACKAGE(nvToolsExt REQUIRED)

SET(LOWLEVELPARTICLES_PLATFORM_INCLUDES
	${NVTOOLSEXT_INCLUDE_DIRS}
)

SET(LLPARTICLES_GPU_SOURCE
	${LL_SOURCE_DIR}/gpu/PtRigidBodyAccessGpu.cpp
)
SOURCE_GROUP(src\\gpu FILES ${LLPARTICLES_GPU_SOURCE})

SET(LOWLEVELPARTICLES_PLATFORM_SRC_FILES
	${LLPARTICLES_GPU_SOURCE}
)

# Use generator expressions to set config specific preprocessor definitions
SET(LOWLEVELPARTICLES_COMPILE_DEFS 

	${PHYSX_WINDOWS_COMPILE_DEFS};PX_PHYSX_STATIC_LIB

	$<$<CONFIG:debug>:${PHYSX_WINDOWS_DEBUG_COMPILE_DEFS};PX_PHYSX_DLL_NAME_POSTFIX=DEBUG;>
	$<$<CONFIG:checked>:${PHYSX_WINDOWS_CHECKED_COMPILE_DEFS};PX_PHYSX_DLL_NAME_POSTFIX=CHECKED;>
	$<$<CONFIG:profile>:${PHYSX_WINDOWS_PROFILE_COMPILE_DEFS};PX_PHYSX_DLL_NAME_POSTFIX=PROFILE;>
	$<$<CONFIG:release>:${PHYSX_WINDOWS_RELEASE_COMPILE_DEFS};>
)

SET(LOWLEVELPARTICLES_LIBTYPE STATIC)

# include common low level particles settings
INCLUDE(../common/LowLevelParticles.cmake)

# Add linked libraries
TARGET_LINK_LIBRARIES(LowLevelParticles PUBLIC ${NVTOOLSEXT_LIBRARIES})
