#
# Build NvCloth (PROJECT not SOLUTION)
#

SET(GW_DEPS_ROOT $ENV{GW_DEPS_ROOT})

SET(NVCLOTH_PERF_TESTS_COMPILE_DEFS

	NV_CLOTH_IMPORT=PX_DLL_EXPORT
	NV_CLOTH_ENABLE_DX11=0
	NV_CLOTH_ENABLE_CUDA=0
	USE_CUDA=0
	USE_DX11=0
	GTEST_HAS_RTTI=0
	GTEST_HAS_TR1_TUPLE=0
	PERF_TEST


	$<$<CONFIG:debug>:${NVCLOTH_PERF_TESTS_MAC_DEBUG_COMPILE_DEFS};PX_PHYSX_DLL_NAME_POSTFIX=DEBUG;_DEBUG>
	$<$<CONFIG:checked>:${NVCLOTH_PERF_TESTS_MAC_CHECKED_COMPILE_DEFS};PX_PHYSX_DLL_NAME_POSTFIX=CHECKED;NDEBUG>
	$<$<CONFIG:profile>:${NVCLOTH_PERF_TESTS_MAC_PROFILE_COMPILE_DEFS};PX_PHYSX_DLL_NAME_POSTFIX=PROFILE;NDEBUG>
	$<$<CONFIG:release>:${NVCLOTH_PERF_TESTS_MAC_RELEASE_COMPILE_DEFS};NDEBUG>
)

SET(NVCLOTH_PERF_TESTS_LIBTYPE SHARED)

# include common NvCloth settings
INCLUDE(../common/NvClothPerfTests.cmake)


# Add linked libraries
# TARGET_LINK_LIBRARIES(PhysX PUBLIC ${NVTOOLSEXT_LIBRARIES} LowLevel LowLevelAABB LowLevelCloth LowLevelDynamics LowLevelParticles PhysXCommon PhysXGpu PxFoundation PxPvdSDK PxTask SceneQuery SimulationController)

TARGET_LINK_LIBRARIES(NvClothPerfTests PUBLIC PxFoundation)
TARGET_LINK_LIBRARIES(NvClothPerfTests PUBLIC GoogleTest)
TARGET_LINK_LIBRARIES(NvClothPerfTests PUBLIC NvCloth)

SET_TARGET_PROPERTIES(NvClothPerfTests PROPERTIES 
	LINK_FLAGS_DEBUG ""
	LINK_FLAGS_CHECKED ""
	LINK_FLAGS_PROFILE ""
	LINK_FLAGS_RELEASE ""
)

# enable -fPIC so we can link static libs with the editor
SET_TARGET_PROPERTIES(NvClothPerfTests PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
