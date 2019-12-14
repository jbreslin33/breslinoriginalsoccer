//-----------------------------------------------------------------------------
// Torque Game Engine Advanced
// Copyright (C) GarageGames.com, Inc.
//-----------------------------------------------------------------------------

#ifndef _TORQUECONFIG_H_
#define _TORQUECONFIG_H_

//-----------------------------------------------------------------------------
//Hi, and welcome to the Torque Config file.
//
//This file is a central reference for the various configuration flags that
//you'll be using when controlling what sort of a Torque build you have. In
//general, the information here is global for your entire codebase, applying
//not only to your game proper, but also to all of your tools.

/// Since we can build different engine "products" out of the same
/// base engine source we need a way to differentiate which product
/// this particular game is using.
///
/// TGE      0001
/// TGEA     0002
/// TGB      0003
/// TGEA 360 0004
/// TGE WII  0005
///
#define TORQUE_ENGINE_PRODUCT      0002

/// What's the name of your application? Used in a variety of places.
#define TORQUE_APP_NAME            "afxDemo"

/// What version of the application specific source code is this?
///
/// Version number is major * 1000 + minor * 100 + revision * 10.
#define TORQUE_APP_VERSION         1120

/// Human readable application version string.
#define TORQUE_APP_VERSION_STRING  "1.1.2"

/// Define me if you want to enable multithreading support.
#define TORQUE_MULTITHREAD

/// Define me if you want to disable Torque memory manager.
#define TORQUE_DISABLE_MEMORY_MANAGER

/// Define me if you don't want Torque to compile dso's
#define TORQUE_NO_DSO_GENERATION

// Define me if this build is a tools build

#ifndef TORQUE_PLAYER
#  define TORQUE_TOOLS
#else
#  undef TORQUE_TOOLS
#endif

/// Define me if you want to enable the profiler.
///    See also the TORQUE_SHIPPING block below
//#define TORQUE_ENABLE_PROFILER

/// Define me to enable unicode support.
#define TORQUE_UNICODE

/// Define me to enable debug mode; enables a great number of additional
/// sanity checks, as well as making AssertFatal and AssertWarn do something.
/// This is usually defined by the build target.
//#define TORQUE_DEBUG

/// Define me if this is a shipping build; if defined I will instruct Torque
/// to batten down some hatches and generally be more "final game" oriented.
/// Notably this disables a liberal resource manager file searching, and
/// console help strings.
//#define TORQUE_SHIPPING

/// Define me to enable a variety of network debugging aids.
//#define TORQUE_DEBUG_NET

/// Enable this define to change the default Net::MaxPacketDataSize
/// Do this at your own risk since it has the potential to cause packets
/// to be split up by old routers and Torque does not have a mechanism to
/// stitch split packets back together. Using this define can be very useful
/// in controlled network hardware environments (like a LAN) or for singleplayer
/// games (like BArricade and its large paths)
//#define MAXPACKETSIZE 1500

/// Modify me to enable metric gathering code in the renderers.
///
/// 0 does nothing; higher numbers enable higher levels of metric gathering.
//#define TORQUE_GATHER_METRICS 0

/// Define me if you want to enable debug guards in the memory manager.
///
/// Debug guards are known values placed before and after every block of
/// allocated memory. They are checked periodically by Memory::validate(),
/// and if they are modified (indicating an access to memory the app doesn't
/// "own"), an error is flagged (ie, you'll see a crash in the memory
/// manager's validate code). Using this and a debugger, you can track down
/// memory corruption issues quickly.
//#define TORQUE_DEBUG_GUARD

/// Define me if you want to enable instanced-static behavior
//#define TORQUE_ENABLE_THREAD_STATICS

/// Define me if you want to gather static-usage metrics
//#define TORQUE_ENABLE_THREAD_STATIC_METRICS

/// Define me if you want to enable debug guards on the FrameAllocator.
/// 
/// This is similar to the above memory manager guards, but applies only to the
/// fast FrameAllocator temporary pool memory allocations. The guards are only
/// checked when the FrameAllocator frees memory (when it's water mark changes).
/// This is most useful for detecting buffer overruns when using FrameTemp<> .
/// A buffer overrun in the FrameAllocator is unlikely to cause a crash, but may
/// still result in unexpected behavior, if other FrameTemp's are stomped.
//#define FRAMEALLOCATOR_DEBUG_GUARD

/// Define to disable Ogg Vorbis audio support. Libs are compiled without this by
/// default.
//#define TORQUE_NO_OGGVORBIS

/// This #define is used by the FrameAllocator to align starting addresses to
/// be byte aligned to this value. This is important on the 360 and possibly
/// on other platforms as well. Use this #define anywhere alignment is needed.
///
/// NOTE: Do not change this value per-platform unless you have a very good
/// reason for doing so. It has the potential to cause inconsistencies in 
/// memory which is allocated and expected to be contiguous.
///
///@ TODO: Make sure that everywhere this should be used, it is being used.
#define TORQUE_BYTE_ALIGNMENT 4

/// This #define should be set if the engine should use a 32-bit format for
/// 24-bit textures. The most notable case is converting RGB->RGBX for various
/// reasons.

// CodeReview: It may be worth determining this at run-time. Right now I just
// want to wrap code which forces the conversion from 24->32 in a common 
// #define so it is easily turned on/off for the problems we are encountering in
// the lighting. [5/11/2007 Pat]
//#define TORQUE_FORCE_24_BIT_TO_32_BIT_TEXTURES

/// This #define is used by the FrameAllocator to set the size of the frame.
///
/// It was previously set to 3MB but I've increased it to 16MB due to the
/// FrameAllocator being used as temporary storage for bitmaps in the D3D9
/// texture manager.
#define TORQUE_FRAME_SIZE     16 << 20

// Finally, we define some dependent #defines. This enables some subsidiary
// functionality to get automatically turned on in certain configurations.

#ifdef TORQUE_DEBUG
#  define TORQUE_GATHER_METRICS 0
#  define TORQUE_ENABLE_PROFILER
#  define TORQUE_ENABLE_PROFILE_PATH
#ifndef TORQUE_DEBUG_GUARD
#  define TORQUE_DEBUG_GUARD
#endif
#endif

#ifdef TORQUE_RELEASE
  // If it's not DEBUG, it's a RELEASE build, put appropriate things here.
#endif

#ifdef TORQUE_SHIPPING
 // TORQUE_SHIPPING flags here.
#else
   // enable the profiler by default, if we're not doing a shipping build
#  define TORQUE_ENABLE_PROFILER
#endif

#if defined(TORQUE_LIB) || defined(TORQUE_OS_XENON)
   #ifndef TORQUE_NO_OGGVORBIS
   #define TORQUE_NO_OGGVORBIS
   #endif
#endif

// This define is for the shader constant include string
#define SHADER_CONSTANT_INCLUDE_FILE "../game/shdrConsts.h"

#ifdef TORQUE_TOOLS
#  define TORQUE_INSTANCE_EXCLUSION   "TorqueToolsTest"
#else
#  define TORQUE_INSTANCE_EXCLUSION   "TorqueTest"
#endif

// This is the lighting system thats enabled by default when the scene graphs are created.
#define DEFAULT_LIGHTING_SYSTEM "SynapseGaming Lighting Kit"
//#define DEFAULT_LIGHTING_SYSTEM "Basic Lighting"

// Someday, it might make sense to do some pragma magic here so we error
// on inconsistent flags.

// The Xbox360 has it's own profiling tools, the Torque Profiler should not be used
#ifdef TORQUE_OS_XENON
#  ifdef TORQUE_ENABLE_PROFILER
#     undef TORQUE_ENABLE_PROFILER
#  endif
#
#  ifdef TORQUE_ENABLE_PROFILE_PATH
#     undef TORQUE_ENABLE_PROFILE_PATH
#endif
#endif


#endif

