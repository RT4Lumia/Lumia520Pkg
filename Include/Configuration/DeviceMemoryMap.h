#ifndef _DEVICE_MEMORY_MAP_H_
#define _DEVICE_MEMORY_MAP_H_

#include <Library/ArmLib.h>

#define MAX_ARM_MEMORY_REGION_DESCRIPTOR_COUNT 64

/* Below flag is used for system memory */
#define SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES \
                EFI_RESOURCE_ATTRIBUTE_PRESENT |                 \
                EFI_RESOURCE_ATTRIBUTE_INITIALIZED |             \
                EFI_RESOURCE_ATTRIBUTE_TESTED |                  \
                EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |             \
                EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |       \
                EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE | \
                EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE |    \
                EFI_RESOURCE_ATTRIBUTE_EXECUTION_PROTECTABLE

typedef enum {
    NoHob,
    AddMem,
    AddDev,
    MaxMem
} DeviceMemoryAddHob;

typedef struct {
	EFI_PHYSICAL_ADDRESS				Address;
	UINT64						Length;
	EFI_RESOURCE_TYPE				ResourceType;
	EFI_RESOURCE_ATTRIBUTE_TYPE			ResourceAttribute;
	ARM_MEMORY_REGION_ATTRIBUTES			ArmAttributes;
	DeviceMemoryAddHob				HobOption;
	EFI_MEMORY_TYPE					MemoryType;
} ARM_MEMORY_REGION_DESCRIPTOR_EX, *PARM_MEMORY_REGION_DESCRIPTOR_EX;

static ARM_MEMORY_REGION_DESCRIPTOR_EX gDeviceMemoryDescriptorEx[] = 
{
	/* MemBase,	  MemSize,     ResourceType, ResourceAttribute,                                  CacheAttributes,                 		 BuildHob,	MemoryType */
	/*SMEM*/
	{ 0x80000000, 0x00200000, EFI_RESOURCE_MEMORY_RESERVED, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED, NoHob, EfiMaxMemoryType },
	/*UEFI FD*/
	{ 0x80200000, 0x00100000, EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK, AddMem, EfiBootServicesCode},
	/*HLOS 0*/
	{ 0x80300000, 0x00100000, EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK, AddMem, EfiConventionalMemory },
	/*Display Reserved*/
 	{ 0x80400000, 0x00800000, EFI_RESOURCE_MEMORY_RESERVED, EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_THROUGH, AddMem, EfiMaxMemoryType },
	/*HLOS 1*/
	{ 0x80500000, 0x01000000, EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK, AddMem, EfiConventionalMemory },
	/*CPU Vectors*/
	{ 0x81500000, 0x00100000, EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK, AddMem, EfiBootServicesData },
	/*UEFI Stack*/
	{ 0x81600000, 0x00040000, EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK, AddMem, EfiBootServicesData },
	/*HLOS 3*/
	{ 0x81640000, 0x02FC0000, EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK, AddMem, EfiConventionalMemory },
	/*HLOS 3*/
	{ 0x84600000, 0x04900000, EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK, AddMem, EfiConventionalMemory },
	//0x8ff00000 ~ 0x90000000 0x00100000   SBL3
    /*HLOS ++*/
    { 0x90000000, 0x10000000, EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK, AddMem, EfiConventionalMemory },

	/* Other memory regions */
	/* Register regions */
	/*MSM_IOMAP*/
	{ 0x00100000, 0x27f00000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddDev, EfiMemoryMappedIO },
	/*LPASS LPASS_CSR_BASE*/
	{ 0x28000000, 0x00B00000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddDev, EfiMemoryMappedIO },
	/*IMEM*/
	{ 0x2A000000, 0x00100000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_INITIALIZED, ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED, NoHob, EfiConventionalMemory},
	/*SBL2*/
	{ 0x2E000000, 0x00100000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddDev, EfiMemoryMappedIO },

	/*1*/
	//{ 0x00500000, 0x00001000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddDev, EfiMemoryMappedIO },
	/*2*/
	//{ 0x00800000, 0x00001000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddDev, EfiMemoryMappedIO },
	/*3*/
	//{ 0x0200A000, 0x00001000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddDev, EfiMemoryMappedIO },
	/* Terminator for MMU*/
	{0},
	/* Terminator for LibMem */
	{ 0xFFFFFFFF, 0x00001000, EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE, ARM_MEMORY_REGION_ATTRIBUTE_DEVICE, AddDev, EfiMemoryMappedIO }

	};

#endif
