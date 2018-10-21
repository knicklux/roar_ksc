#ifndef KSC__VISIBILITY_CONTROL_H_
#define KSC__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define KSC_EXPORT __attribute__ ((dllexport))
    #define KSC_IMPORT __attribute__ ((dllimport))
  #else
    #define KSC_EXPORT __declspec(dllexport)
    #define KSC_IMPORT __declspec(dllimport)
  #endif
  #ifdef KSC_BUILDING_LIBRARY
    #define KSC_PUBLIC KSC_EXPORT
  #else
    #define KSC_PUBLIC KSC_IMPORT
  #endif
  #define KSC_PUBLIC_TYPE KSC_PUBLIC
  #define KSC_LOCAL
#else
  #define KSC_EXPORT __attribute__ ((visibility("default")))
  #define KSC_IMPORT
  #if __GNUC__ >= 4
    #define KSC_PUBLIC __attribute__ ((visibility("default")))
    #define KSC_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define KSC_PUBLIC
    #define KSC_LOCAL
  #endif
  #define KSC_PUBLIC_TYPE
#endif

#endif  // KSC__VISIBILITY_CONTROL_H_
