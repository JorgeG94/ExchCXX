
#ifdef HAVE_HIP
#define cudaStream_t hipStream_t
#include <hip/hip_runtime.h>
#elif HAVE_CUDA
#include <cuda_runtime.h>
#endif 

#ifdef HAVE_CUDA
void throw_if_fail( cudaError_t stat, std::string msg ) {
  if( stat != cudaSuccess ) throw std::runtime_error( msg );
}
#elif HAVE_HIP
void throw_if_fail( hipError_t stat, std::string msg ) {
  if( stat != hipSuccess ) throw std::runtime_error( msg );
}
#endif

void copy_async(void* dest, const void* src, const size_t len, cudaStream_t& stream) {
  #ifdef HAVE_CUDA
  auto stat = cudaMemcpyAsync(dest, src, len, cudaMemcpyDefault, stream);
  #elif HAVE_HIP
  auto stat = hipMemcpyAsync(dest, src, len, hipMemcpyDefault, stream);
  #endif
  throw_if_fail(stat, "copy failed"); 
}

void copy(void* dest, const void* src, const size_t len) {
  #ifdef HAVE_CUDA 
  auto stat = cudaMemcpy(dest, src, len, cudaMemcpyDefault);
  #elif HAVE_HIP
  auto stat = hipMemcpy(dest, src, len, hipMemcpyDefault);
  #endif
  throw_if_fail(stat, "copy failed"); 
}

void streamsync(cudaStream_t& stream) {
  #ifdef HAVE_CUDA
  auto stat  = cudaStreamSynchronize(stream);
  #elif HAVE_HIP
  auto stat = hipStreamSynchronize(stream);
  #endif
  throw_if_fail(stat, "copy failed"); 
}