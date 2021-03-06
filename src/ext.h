/* Include OpenCL header, and define OpenCL extensions, since what is and is not
 * available in the official headers is very system-dependent */

#ifndef _EXT_H
#define _EXT_H

/* We will use the deprecated clGetExtensionFunctionAddress,
 * so let the headers know that we don't care about it being deprecated.
 * The standard CL_USE_DEPRECATED_OPENCL_1_1_APIS define apparently
 * doesn't work for macOS, so we'll just tell the compiler to not
 * warn about deprecated functions.
 * A more correct solution would be to suppress the warning only around the
 * clGetExtensionFunctionAddress call, but honestly I just cleaned up that
 * piece of code. And I'm actually wondering if it even makes sense to
 * build that part of the code on macOS: does anybody actually use
 * ocl-icd as OpenCL dispatcher on macOS?
 */

#ifdef __APPLE__
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <OpenCL/opencl.h>
#else
#define CL_USE_DEPRECATED_OPENCL_1_1_APIS
#include <CL/cl.h>
#endif

/* These two defines were introduced in the 1.2 headers
 * on 2012-11-30, so earlier versions don't have them
 * (e.g. Debian wheezy)
 */

#ifndef CL_DEVICE_IMAGE_PITCH_ALIGNMENT
#define CL_DEVICE_IMAGE_PITCH_ALIGNMENT                 0x104A
#define CL_DEVICE_IMAGE_BASE_ADDRESS_ALIGNMENT          0x104B
#endif

/* 2.0 headers are not very common for the time being, so
 * let's copy the defines for the new CL_DEVICE_* properties
 * here.
 */
#ifndef CL_VERSION_2_0
#define CL_DEVICE_MAX_READ_WRITE_IMAGE_ARGS             0x104C
#define CL_DEVICE_MAX_GLOBAL_VARIABLE_SIZE              0x104D
#define CL_DEVICE_QUEUE_ON_DEVICE_PROPERTIES            0x104E
#define CL_DEVICE_QUEUE_ON_DEVICE_PREFERRED_SIZE        0x104F
#define CL_DEVICE_QUEUE_ON_DEVICE_MAX_SIZE              0x1050
#define CL_DEVICE_MAX_ON_DEVICE_QUEUES                  0x1051
#define CL_DEVICE_MAX_ON_DEVICE_EVENTS                  0x1052
#define CL_DEVICE_SVM_CAPABILITIES                      0x1053
#define CL_DEVICE_GLOBAL_VARIABLE_PREFERRED_TOTAL_SIZE  0x1054
#define CL_DEVICE_MAX_PIPE_ARGS                         0x1055
#define CL_DEVICE_PIPE_MAX_ACTIVE_RESERVATIONS          0x1056
#define CL_DEVICE_PIPE_MAX_PACKET_SIZE                  0x1057
#define CL_DEVICE_PREFERRED_PLATFORM_ATOMIC_ALIGNMENT   0x1058
#define CL_DEVICE_PREFERRED_GLOBAL_ATOMIC_ALIGNMENT     0x1059
#define CL_DEVICE_PREFERRED_LOCAL_ATOMIC_ALIGNMENT      0x105A

#define CL_DEVICE_SVM_COARSE_GRAIN_BUFFER           (1 << 0)
#define CL_DEVICE_SVM_FINE_GRAIN_BUFFER             (1 << 1)
#define CL_DEVICE_SVM_FINE_GRAIN_SYSTEM             (1 << 2)
#define CL_DEVICE_SVM_ATOMICS                       (1 << 3)

typedef cl_bitfield         cl_device_svm_capabilities;
#endif

#ifndef CL_VERSION_2_1
#define CL_PLATFORM_HOST_TIMER_RESOLUTION		0x0905
#define CL_DEVICE_IL_VERSION				0x105B
#define CL_DEVICE_MAX_NUM_SUB_GROUPS			0x105C
#define CL_DEVICE_SUB_GROUP_INDEPENDENT_FORWARD_PROGRESS 0x105D
#endif

/*
 * Extensions
 */

/* cl_khr_icd */
#define CL_PLATFORM_ICD_SUFFIX_KHR			0x0920
#define CL_PLATFORM_NOT_FOUND_KHR			-1001


/* cl_khr_fp64 */
#define CL_DEVICE_DOUBLE_FP_CONFIG			0x1032

/* cl_khr_fp16 */
#define CL_DEVICE_HALF_FP_CONFIG			0x1033

/* cl_khr_terminate_context */
#define CL_DEVICE_TERMINATE_CAPABILITY_KHR		0x200F

/* TODO: I cannot find official definitions for these,
 * so I'm currently extrapolating them from the specification
 */
typedef cl_bitfield cl_device_terminate_capability_khr;
#define CL_DEVICE_TERMINATE_CAPABILITY_CONTEXT_KHR	(1<<0)

/* cl_khr_subgroup_named_barrier */
#define CL_DEVICE_MAX_NAMED_BARRIER_COUNT_KHR		0x2035

/* cl_nv_device_attribute_query */
#define CL_DEVICE_COMPUTE_CAPABILITY_MAJOR_NV		0x4000
#define CL_DEVICE_COMPUTE_CAPABILITY_MINOR_NV		0x4001
#define CL_DEVICE_REGISTERS_PER_BLOCK_NV		0x4002
#define CL_DEVICE_WARP_SIZE_NV				0x4003
#define CL_DEVICE_GPU_OVERLAP_NV			0x4004
#define CL_DEVICE_KERNEL_EXEC_TIMEOUT_NV		0x4005
#define CL_DEVICE_INTEGRATED_MEMORY_NV			0x4006
#define CL_DEVICE_ATTRIBUTE_ASYNC_ENGINE_COUNT_NV	0x4007
#define CL_DEVICE_PCI_BUS_ID_NV				0x4008
#define CL_DEVICE_PCI_SLOT_ID_NV			0x4009

/* cl_ext_atomic_counters_{32,64} */
#define CL_DEVICE_MAX_ATOMIC_COUNTERS_EXT		0x4032

/* cl_amd_device_attribute_query */
#define CL_DEVICE_PROFILING_TIMER_OFFSET_AMD		0x4036
#define CL_DEVICE_TOPOLOGY_AMD				0x4037
#define CL_DEVICE_BOARD_NAME_AMD			0x4038
#define CL_DEVICE_GLOBAL_FREE_MEMORY_AMD		0x4039
#define CL_DEVICE_SIMD_PER_COMPUTE_UNIT_AMD		0x4040
#define CL_DEVICE_SIMD_WIDTH_AMD			0x4041
#define CL_DEVICE_SIMD_INSTRUCTION_WIDTH_AMD		0x4042
#define CL_DEVICE_WAVEFRONT_WIDTH_AMD			0x4043
#define CL_DEVICE_GLOBAL_MEM_CHANNELS_AMD		0x4044
#define CL_DEVICE_GLOBAL_MEM_CHANNEL_BANKS_AMD		0x4045
#define CL_DEVICE_GLOBAL_MEM_CHANNEL_BANK_WIDTH_AMD	0x4046
#define CL_DEVICE_LOCAL_MEM_SIZE_PER_COMPUTE_UNIT_AMD	0x4047
#define CL_DEVICE_LOCAL_MEM_BANKS_AMD			0x4048
#define CL_DEVICE_THREAD_TRACE_SUPPORTED_AMD		0x4049
#define CL_DEVICE_GFXIP_MAJOR_AMD			0x404A
#define CL_DEVICE_GFXIP_MINOR_AMD			0x404B
#define CL_DEVICE_AVAILABLE_ASYNC_QUEUES_AMD		0x404C

#ifndef CL_DEVICE_TOPOLOGY_TYPE_PCIE_AMD
#define CL_DEVICE_TOPOLOGY_TYPE_PCIE_AMD		1

typedef union
{
	struct { cl_uint type; cl_uint data[5]; } raw;
	struct { cl_uint type; cl_char unused[17]; cl_char bus; cl_char device; cl_char function; } pcie;
} cl_device_topology_amd;
#endif

/* cl_amd_offline_devices */
#define CL_CONTEXT_OFFLINE_DEVICES_AMD			0x403F

/* cl_ext_device_fission */
#define cl_ext_device_fission				1

typedef cl_ulong  cl_device_partition_property_ext;

#define CL_DEVICE_PARTITION_EQUALLY_EXT			0x4050
#define CL_DEVICE_PARTITION_BY_COUNTS_EXT		0x4051
#define CL_DEVICE_PARTITION_BY_NAMES_EXT		0x4052
#define CL_DEVICE_PARTITION_BY_NAMES_INTEL		0x4052 /* cl_intel_device_partition_by_names */
#define CL_DEVICE_PARTITION_BY_AFFINITY_DOMAIN_EXT	0x4053

#define CL_DEVICE_PARENT_DEVICE_EXT			0x4054
#define CL_DEVICE_PARTITION_TYPES_EXT			0x4055
#define CL_DEVICE_AFFINITY_DOMAINS_EXT			0x4056
#define CL_DEVICE_REFERENCE_COUNT_EXT			0x4057
#define CL_DEVICE_PARTITION_STYLE_EXT			0x4058

#define CL_AFFINITY_DOMAIN_L1_CACHE_EXT			0x1
#define CL_AFFINITY_DOMAIN_L2_CACHE_EXT			0x2
#define CL_AFFINITY_DOMAIN_L3_CACHE_EXT			0x3
#define CL_AFFINITY_DOMAIN_L4_CACHE_EXT			0x4
#define CL_AFFINITY_DOMAIN_NUMA_EXT			0x10
#define CL_AFFINITY_DOMAIN_NEXT_FISSIONABLE_EXT		0x100

/* cl_intel_advanced_motion_estimation */
#define CL_DEVICE_ME_VERSION_INTEL			0x407E

/* cl_intel_device_side_avc_motion_estimation */
#define CL_DEVICE_AVC_ME_VERSION_INTEL				0x410B
#define CL_DEVICE_AVC_ME_SUPPORTS_TEXTURE_SAMPLER_USE_INTEL	0x410C
#define CL_DEVICE_AVC_ME_SUPPORTS_PREEMPTION_INTEL		0x410D

/* cl_intel_planar_yuv */
#define CL_DEVICE_PLANAR_YUV_MAX_WIDTH_INTEL		0x417E
#define CL_DEVICE_PLANAR_YUV_MAX_HEIGHT_INTEL		0x417F

/* cl_qcom_ext_host_ptr */
#define CL_DEVICE_EXT_MEM_PADDING_IN_BYTES_QCOM		0x40A0
#define CL_DEVICE_PAGE_SIZE_QCOM			0x40A1

/* cl_arm_shared_virtual_memory */
#define CL_DEVICE_SVM_CAPABILITIES_ARM			0x40B6

/* cl_khr_spir */
#define CL_DEVICE_SPIR_VERSIONS				0x40E0

/* cl_altera_device_temperature */
#define CL_DEVICE_CORE_TEMPERATURE_ALTERA		0x40F3

/* cl_intel_simultaneous_sharing */
#define CL_DEVICE_SIMULTANEOUS_INTEROPS_INTEL		0x4104
#define CL_DEVICE_NUM_SIMULTANEOUS_INTEROPS_INTEL	0x4105

/* cl_intel_required_subgroup_size */
#define CL_DEVICE_SUB_GROUP_SIZES_INTEL			0x4108

#endif
