#pragma once

#ifdef __cplusplus
#   define EXTERN extern "C"
#else
#   define EXTERN
#endif

#define EXPORT(RET) EXTERN RET __attribute__ ((visibility ("default")))
