<div align=center>
	<img src="https://i.postimg.cc/Y95Sr2J6/lumi-logo.png" alt="logo">
</div>

<div align=center>
	<img src="https://img.shields.io/badge/license-Zlib-green?style=plastic" alt="license">
	<img src="https://img.shields.io/github/v/release/NexusWasLost/Lumi?style=plastic" alt="latest release">
	<img src="https://img.shields.io/badge/platform-Windows-pink?style=plastic" alt="latest release">
</div>

<br><br>
**Lumi** is a lightweight C library built for fetching system information on Windows. Lumi is written in C and is fully compatible with C++.

<br>

## Getting Started

To get started with Lumi, download the [latest release]() or see [building Lumi from source]().<br><br>

Here is a code example to get a taste of Lumi:

```c
#include <stdio.h>
#include "lumi.h"
#include "lumi_functions.h"

int main(){
	LUMI lumi; //define a LUMI variable

	getCPU(&lumi); //call needed function
	getMemory(&lumi);
	getDisplay(&lumi);
	getNetwork(&lumi);

	//print the info
	printf("CPU: %s\n", lumi.CPU);
	printf("RAM: %llu MB / %llu MB\n", lumi.usedMemory, lumi.totalMemory);

	//print all active displays.
	for(int x = 0; x < lumi.displayCount; x++){
		printf("Display %d: %d x %d @ %d Hz\n",
		 x + 1,
		 lumi.monitors[x].width, lumi.monitors[x].height, lumi.monitors[x].refreshRate
		);
	}

	return 0;
}
```

Create a file called `main.c` and paste the above given code, then compile using GCC (assuming Lumi version 4.0.0):

```shell
gcc main.c -o main.exe -I./Lumi_v4.0.0/include -L./Lumi_v4.0.0/lib -llumi -ldxgi -ldxguid -lole32 -liphlpapi
```

This is will output a `main.exe` which can be ran using: `./main.exe` !<br><br>

## Supported Constraints

- **Operating Systems:** Windows 10 and Windows 11 (tested).
- **CPU Architectures:** x86_64 (AMD64); x86 (32-bit, not tested).

**Maximum Supported Hardware:**
- Displays: 6.
- GPUs: 4.
- Network adapters: 32.
- Disks: 32.

These limits can be adjusted by modifying the corresponding macros and rebuilding the library.

**Compilers:**
- [GCC (MinGW)](https://nuwen.net/mingw.html): Fully supported and primarily used for development.
- [Clang](https://clang.llvm.org/): Expected to work, but not tested.
- [MSVC](https://visualstudio.microsoft.com/vs/features/cplusplus/): Not supported without source code modifications and rebuilding the library.
<br>

## Building Lumi from Source

The library can be built from source if needed.

1. Clone the repository

```shell
git clone https://github.com/NexusWasLost/Lumi.git
```

2. Navigate into the directory

```shell
cd Lumi
```

### 🔸 Compiling using GCC (MinGW) or Clang

Lumi is primarily compiled using GCC (MinGW) and should work with Clang though not tested.


1. Initialize CMake
```shell
cmake -B build -G "MinGW Makefiles"
```

2. Build the library
```shell
cmake --build build
```

This will output `liblumi.a` inside a build directory inside the project root.

### 🔸 Compiling using MSVC

To build Lumi using MSVC, few things in the source code needs to be changed, moreover compiling using MSVC is not tested.

View [Changes needed while compiling using MSVC](). After making those changes to source code follow the below steps to build the library:

1. Initialize CMake (CMake targets MSVC NMake by default on Windows)
```shell
cmake -B build
```

2. Build the library
```shell
cmake --build build
```

This should output `liblumi.lib` inside a build directory inside the project root.<br><br>

## List of Functions

| Function                              | Description                                                                                                                  |
| ------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------- |
| `void getMemory(LUMI* lumi)`          | Retrieves total, available, and used physical memory, along with memory load.                                                |
| `void getCPU(LUMI* lumi)`             | Retrieves the CPU brand string and architecture.                                                                             |
| `void getGPU(LUMI* lumi)`             | Retrieves graphics adapter names and total VRAM for each adapter.                                                            |
| `void getOS(LUMI* lumi)`              | Retrieves the Windows product name, version, and build number.                                                               |
| `void getDisplay(LUMI* lumi)`         | Retrieves the resolution and refresh rate of each active display.                                                            |
| `void getCurrentUsername(LUMI* lumi)` | Retrieves the current username.                                                                                              |
| `void getHostName(LUMI* lumi)`        | Retrieves the computer's hostname.                                                                                           |
| `void getUptime(LUMI* lumi)`          | Retrieves system uptime in seconds.                                                                                          |
| `void getLocale(LUMI* lumi)`          | Retrieves the system locale.                                                                                                 |
| `void getNetwork(LUMI* lumi)`         | Retrieves information about active network adapters.                                                                         |
| `void getDisk(LUMI* lumi)`            | Retrieves disk information, including drive letter, volume label, free space, used space, total space, and file system name. |

<br>

## List of Fields

| Field                 | Type                                             | Function               | Description                          |
| --------------------- | ------------------------------------------------ | ---------------------- | ------------------------------------ |
| `CPU`                 | `char[49]`                                       | `getCPU()`             | CPU brand string.                    |
| `CPU_Architecture`    | `char[8]`                                        | `getCPU()`             | CPU architecture.                    |
| `OS_ProductName`      | `char[OS_PRODUCT_NAME_SIZE]`                     | `getOS()`              | Windows product name.                |
| `OS_Version`          | `char[OS_VERSION_SIZE]`                          | `getOS()`              | Windows version string.              |
| `OS_BuildNumber`      | `char[OS_BUILD_NUMBER_SIZE]`                     | `getOS()`              | Windows build number.                |
| `host`                | `char[16]`                                       | `getHostName()`        | Computer hostname.                   |
| `locale`              | `wchar_t[16]`                                    | `getLocale()`          | System locale.                       |
| `currentUserName`     | `char[32]`                                       | `getCurrentUsername()` | Current username.                    |
| `totalMemory`         | `unsigned long long`                             | `getMemory()`          | Total physical memory in MB.         |
| `availableMemory`     | `unsigned long long`                             | `getMemory()`          | Available physical memory in MB.     |
| `usedMemory`          | `unsigned long long`                             | `getMemory()`          | Used physical memory in MB.          |
| `memoryLoad`          | `unsigned long long`                             | `getMemory()`          | Current memory load as a percentage. |
| `uptime`              | `unsigned long long`                             | `getUptime()`          | System uptime in seconds.            |
| `gpu`                 | [`GPU[MAX_GPU_COUNT]`](#)                        | `getGPU()`             | Array of detected GPUs.              |
| `gpuCount`            | `size_t`                                         | `getGPU()`             | Number of detected GPUs.             |
| `monitors`            | [`Display[MAX_DISPLAY_COUNT]`](#)                | `getDisplay()`         | Array of active displays.            |
| `displayCount`        | `size_t`                                         | `getDisplay()`         | Number of active displays.           |
| `net_Adapters`        | [`NetworkAdapter[MAX_NETWORK_ADAPTER_COUNT]`](#) | `getNetwork()`         | Array of active network adapters.    |
| `networkAdapterCount` | `size_t`                                         | `getNetwork()`         | Number of active network adapters.   |
| `disks`               | [`Disk[MAX_DISK_COUNT]`](#)                      | `getDisk()`            | Array of detected disks.             |
| `diskCount`           | `size_t`                                         | `getDisk()`            | Number of detected disks.            |

Each function called once will populate every field related to that particular function. For example `getCPU()` will populate `CPU` and `CPU Architecture` field with just one call.<br>

### Sub Structs

#### Display

| Field         | Type  | Description                 |
| ------------- | ----- | --------------------------- |
| `width`       | `int` | Display width in pixels.    |
| `height`      | `int` | Display height in pixels.   |
| `refreshRate` | `int` | Display refresh rate in Hz. |

#### GPU

| Field       | Type                     | Description               |
| ----------- | ------------------------ | ------------------------- |
| `GPU_Name`  | `wchar_t[GPU_NAME_SIZE]` | GPU name.                 |
| `totalVRAM` | `unsigned long long`     | Total video memory in MB. |

#### NetworkAdapter

| Field                | Type                                 | Description                  |
| -------------------- | ------------------------------------ | ---------------------------- |
| `networkAdapterName` | `wchar_t[NETWORK_ADAPTER_NAME_SIZE]` | Network adapter name.        |
| `networkAdapterDesc` | `wchar_t[NETWORK_ADAPTER_DESC_SIZE]` | Network adapter description. |


#### Disk

| Field            | Type                         | Description                 |
| ---------------- | ---------------------------- | --------------------------- |
| `volumeLabel`    | `wchar_t[MAX_PATH + 1]`      | Disk volume label.          |
| `fileSystemName` | `wchar_t[DISK_FS_NAME_SIZE]` | File system name.           |
| `diskLetter`     | `wchar_t`                    | Drive letter.               |
| `freeSpace`      | `double`                     | Available disk space in GB. |
| `usedSpace`      | `double`                     | Used disk space in GB.      |
| `totalSpace`     | `double`                     | Total disk space in GB.     |

<br>

## 🔹 Changes needed while compiling using MSVC

(Not Tested) In `cpu.c`, replace GCC specific - `<cpuid.h>` and `__get_cpuid()` with MSVC equivalents:

```c
...
#include <intrin.h> //include intrin.h instead of cpuid.h
...
void getCPU(LUMI* lumi){
	...
	int cpuBrandString[4];
	for(int x = 0; x < 3; x++){
		__cpuid(cpuBrandString, 0x80000002 + x) //call __cpuid()
		...
	}
}
```

<br>

## How Does it Work ?

Lumi uses a mix of WinAPI, Registry Query, `cpuid` and `DXGI` to get system information.
Lumi functions accepts a single parameter which is a pointer to a `LUMI` struct (`LUMI*`).
The variable of type `LUMI` is passed by address, and each function populates it with corresponding system information.

### 🔹 WinAPI

The Windows API (WinAPI) is the native API provided by Microsoft to interact directly with the Operating System.

Lumi uses a handful of lightweight WinAPI calls to fetch system level details like hostname, uptime, locale, etc. Functions such as `GetTickCount64()`(uptime), `GetUserNameA()`(username) and `GetComputerNameA()`(hostname) are directly used to extract these information.

The `GetNativeSystemInfo()` function is used to extract CPU architecture.

For getting display resolution and refresh rate of each available display `EnumDisplayDevices()` and `EnumDisplaySettings()` are used.

### 🔹 Registry Query

Windows registry is a hierarchical database storing config data for OS and installed software.

Lumi queries specific registry keys to obtain necessary details like OS product name, version and build number.

It uses `RegOpenKeyExA()` and `RegQueryValueExA()` to read these keys safely from `HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion`, avoiding the complexity of manual registry access.

### 🔹 DXGI (DirectX Graphics Infrastructure)

DXGI is part of the DirectX family and provides API for Graphics and GPU related information.

Lumi uses `DXGI` interfaces like `IDXGIFactory1()` and `IDXGIAdapter1()` to fetch GPU information such as GPU names, VRAM size and total number of adapters.

### 🔹 CPUID

`cpuid` is a processor instruction that returns detailed information about the CPU such as its Brand, features, etc.

Lumi uses it to get the full CPU Brand String. Since it uses `cpuid` this limits Lumi to just x86 and x86_64 (AMD64) systems only.

---

### Why did I make it ?

Initially I thought of making it as a neofetch/fastfetch equivalent for Windows but after seeing how ridiculously hard it is to get simple system information on Windows I thought of turning this into a library that will help getting info on Windows, and I wanted to build something too so that was enough excuse to build it.

Windows itself was not made for transparency and hence is not at all dev friendly by any means (at least I see it that way). WinAPI or the Windows SDK in general is quite challenging piece of tech I have ever worked with. But...
this project taught me a lot and I mean a lot, this was the first time using low level APIs like `DXGI` and WinAPI and I also learned makefiles for building this project. Moreover, I learned about compiler flags such as `-I` and `-L`,  building a static library and shipping it with headers.

Though not a full blown library it is a cool side project if considered. Learned a lot and really loved making this project equally frustrating and fun.

---

## References

- WinAPI reference: [https://learn.microsoft.com/en-us/windows/win32/api/](https://learn.microsoft.com/en-us/windows/win32/api/)

- Network related API: [https://learn.microsoft.com/en-us/windows/win32/api/iptypes/ns-iptypes-ip_adapter_addresses_lh](https://learn.microsoft.com/en-us/windows/win32/api/iptypes/ns-iptypes-ip_adapter_addresses_lh)

- `swprintf`: [https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/sprintf-sprintf-l-swprintf-swprintf-l-swprintf-l?view=msvc-170](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/sprintf-sprintf-l-swprintf-swprintf-l-swprintf-l?view=msvc-170)

- Stack Overflow: [https://stackoverflow.com/questions](https://stackoverflow.com/questions)

## Additional Info

- Lumi used `cpuid` to get processor brand so it will not work on ARM - based Windows machines.

- I did AI-assisted coding to learn about WinAPI, `DXGI`, Registry Query and the whole project. I preferred AI  over MS Docs in many cases because it was easier to understand the stuff. With that said I didn't copy paste code, I wrote what I understood.

- I will *try* to keep this library updated as needed alongside the documentation.

## Credits

- Thanks to [Arpan](https://github.com/arpank01) for testing it out, helped me find bugs and issues.
