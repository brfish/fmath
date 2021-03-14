#ifndef _FMATH_COMPILE_CONFIG_H_
#define _FMATH_COMPILE_CONFIG_H_

#if defined(__GNUC__)
#   define FMATH_COMPILER_GCC
#elif defined(__MSC_VER)
#   define FMATH_COMPILER_MSVC
#elif defined(__BORLANDC__)
#   define FMATH_COMPILER_BORLANDC
#elif defined(__clang__)
#   define FMATH_COMPILER_CLANG
#else
#   define FMATH_COMPILER_UNKNOWN
#endif

#if __cplusplus >= 201703
#   define FMATH_CXX17_OR_LATER
#endif

#if __cplusplus >= 201402
#   define FMATH_CXX14_OR_LATER
#endif

#if __cplusplus >= 201103
#   define FMATH_CXX11_OR_LATER
#endif

#if defined(FMATH_COMPILER_GCC)
#   define FMATH_ALWAYS_INLINE __attribute__((always_inline)) inline
#elif defined(FMATH_COMPILER_MSVC)
#   define FMATH_ALWAYS_INLINE __forceinline
#else
#   define FMATH_ALWAYS_INLINE inline
#endif

#if defined(FMATH_OPTION_FORCEINLINE)
#   define FMATH_INLINE FMATH_ALWAYS_INLINE
#else
#   define FMATH_INLINE inline
#endif

#if defined(FMATH_CXX_14_OR_LATER)
#   define FMATH_CONSTEXPR constexpr
#else
#   define FMATH_CONSTEXPR
#endif



#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WINDOWS__)
#   define FMATH_PLATFORM_WIN32
#elif defined(__linux__) || defined(linux) || defined(__linux)
#   define FMATH_PLATFORM_LINUX
#elif defined(__APPLE__) || defined(__MACH__)
#   define FMATH_PLATFORM_MACOS
#endif

#if INTPTR_MAX == INT64_MAX
#   define FMATH_ARCHITECTURE_X86_64
#elif INTPTR_MAX == INT32_MAX
#   define FMATH_ARCHITECTURE_X86
#endif

#if defined(FMATH_COMPILER_GCC) || defined(FMATH_COMPILER_CLANG)
#   if defined(FMATH_PLATFORM_WIN32)
#       define FMATH_IMPORT __declspec(dllimport)
#       define FMATH_EXPORT __declspec(dllexport)
#       define FMATH_HIDDEN static
#   elif defined(FMATH_PLATFORM_LINUX)
#       define FMATH_IMPORT __attribute__((visibility("default")))
#       define FMATH_EXPORT __attribute__((visibility("default")))
#       define FMATH_HIDDEN __attribute__((visibility("hidden")))
#   endif
#elif defined(FMATH_COMPILER_MSVC)
#   define FMATH_IMPORT __declspec(dllimport)
#   define FMATH_EXPORT __declspec(dllexport)
#   define FMATH_HIDDEN static
#else
#   define FMATH_IMPORT
#   define FMATH_EXPORT
#   define FMATH_HIDDEN static
#endif

#if defined(FMATH_LIB_EXPORT)
#   define FMATH_API FMATH_EXPORT
#   define FMATH_INTERNAL FMATH_HIDDEN
#else
#   define FMATH_API
#   define FMATH_INTERNAL static
#endif

namespace fmath
{


}

#endif