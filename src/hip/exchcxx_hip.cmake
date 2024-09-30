set( EXCHCXX_HIP_SOURCES 
  hip/xc_functional_device.hip 
  hip/libxc_device.hip 
  hip/builtin.hip
)

find_package( hip REQUIRED )

target_sources( exchcxx PRIVATE ${EXCHCXX_HIP_SOURCES} )
target_link_libraries( exchcxx PUBLIC hip::host )
if (CMAKE_HIP_PLATFORM MATCHES "nvidia")
    target_include_directories( exchcxx PUBLIC ${HIP_INCLUDE_DIRS} )
    target_compile_definitions( exchcxx PUBLIC __HIP_PLATFORM_NVIDIA__ )
    find_package ( CUDAToolkit REQUIRED )
    target_link_libraries( exchcxx PUBLIC CUDA::cudart )
endif()
