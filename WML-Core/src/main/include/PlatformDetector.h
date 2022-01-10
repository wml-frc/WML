#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   #define WML_PLATFORM_WINDOWS

   #ifdef _WIN64
      #define WML_PLATFORM_WINDOWS_X86_64
   #else
      #define WML_PLATFORM_WINDOWS_X86
   #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
      // iOS, tvOS, or watchOS Simulator
    #elif TARGET_OS_MACCATALYST
      // Mac's Catalyst (ports iOS API into Mac, like UIKit).
    #elif TARGET_OS_IPHONE
      #define WML_PLATFORM_IOS
    #elif TARGET_OS_MAC
      #define WML_PLATFORM_MACOS
    #else
      #error "Unknown Apple platform"
    #endif
#elif __linux__
  #define WML_PLATFORM_LINUX
  #define WML_PLATFORM_UNIX
#elif __unix__ // all unices not caught above
  #define WML_PLATFORM_UNIX

#elif defined(_POSIX_VERSION)
  #define WML_PLATFORM_POSIX
#else
  #error "Unknown compiler"
#endif