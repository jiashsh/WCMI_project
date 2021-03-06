#include <__threading_support>
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <process.h>
#include <fibersapi.h>

#include <chrono>

_LIBCPP_BEGIN_NAMESPACE_STD

static_assert(sizeof(__libcpp_recursive_mutex_t) == sizeof(CRITICAL_SECTION), "incorrect __libcpp_recursive_mutex_t size");
static_assert(alignof(__libcpp_recursive_mutex_t) == alignof(CRITICAL_SECTION), "incorrect __libcpp_recursive_mutex_t alignment");

// Mutex
int __libcpp_recursive_mutex_init(__libcpp_recursive_mutex_t *__m)
{
  InitializeCriticalSection(reinterpret_cast<CRITICAL_SECTION*>(__m));
  return 0;
}

int __libcpp_recursive_mutex_lock(__libcpp_recursive_mutex_t *__m)
{
  EnterCriticalSection(reinterpret_cast<CRITICAL_SECTION*>(__m));
  return 0;
}

bool __libcpp_recursive_mutex_trylock(__libcpp_recursive_mutex_t *__m)
{
  return TryEnterCriticalSection(reinterpret_cast<CRITICAL_SECTION*>(__m)) != 0;
}

int __libcpp_recursive_mutex_unlock(__libcpp_recursive_mutex_t *__m)
{
  LeaveCriticalSection(reinterpret_cast<CRITICAL_SECTION*>(__m));
  return 0;
}

int __libcpp_recursive_mutex_destroy(__libcpp_recursive_mutex_t *__m)
{
  DeleteCriticalSection(reinterpret_cast<CRITICAL_SECTION*>(__m));
  return 0;
}

static_assert(sizeof(__libcpp_mutex_t) == sizeof(SRWLOCK), "incorrect __libcpp_mutex_t size");
static_assert(alignof(__libcpp_mutex_t) == alignof(SRWLOCK), "incorrect __libcpp_mutex_t alignment");

int __libcpp_mutex_lock(__libcpp_mutex_t *__m)
{
  AcquireSRWLockExclusive(reinterpret_cast<SRWLOCK*>(__m));
  return 0;
}

bool __libcpp_mutex_trylock(__libcpp_mutex_t *__m)
{
  return TryAcquireSRWLockExclusive(reinterpret_cast<SRWLOCK*>(__m)) != 0;
}

int __libcpp_mutex_unlock(__libcpp_mutex_t *__m)
{
  ReleaseSRWLockExclusive(reinterpret_cast<SRWLOCK*>(__m));
  return 0;
}

int __libcpp_mutex_destroy(__libcpp_mutex_t *__m)
{
  static_cast<void>(__m);
  return 0;
}

// Condition Variable
static_assert(sizeof(__libcpp_condvar_t) == sizeof(CONDITION_VARIABLE), "incorrect __libcpp_condvar_t size");
static_assert(alignof(__libcpp_condvar_t) == alignof(CONDITION_VARIABLE), "incorrect __libcpp_condvar_t alignment");

int __libcpp_condvar_signal(__libcpp_condvar_t *__cv)
{
  WakeConditionVariable(reinterpret_cast<CONDITION_VARIABLE*>(__cv));
  return 0;
}

int __libcpp_condvar_broadcast(__libcpp_condvar_t *__cv)
{
  WakeAllConditionVariable(reinterpret_cast<CONDITION_VARIABLE*>(__cv));
  return 0;
}

int __libcpp_condvar_wait(__libcpp_condvar_t *__cv, __libcpp_mutex_t *__m)
{
  SleepConditionVariableSRW(reinterpret_cast<CONDITION_VARIABLE*>(__cv),
                            reinterpret_cast<SRWLOCK*>(__m), INFINITE, 0);
  return 0;
}

int __libcpp_condvar_timedwait(__libcpp_condvar_t *__cv, __libcpp_mutex_t *__m,
                               timespec *__ts)
{
  using namespace _VSTD::chrono;

  auto duration = seconds(__ts->tv_sec) + nanoseconds(__ts->tv_nsec);
  auto abstime =
      system_clock::time_point(duration_cast<system_clock::duration>(duration));
  auto timeout_ms = duration_cast<milliseconds>(abstime - system_clock::now());

  if (!SleepConditionVariableSRW(reinterpret_cast<CONDITION_VARIABLE*>(__cv),
                                 reinterpret_cast<SRWLOCK*>(__m),
                                 timeout_ms.count() > 0 ? timeout_ms.count()
                                                        : 0,
                                 0))
    {
      auto __ec = GetLastError();
      return __ec == ERROR_TIMEOUT ? ETIMEDOUT : __ec;
    }
  return 0;
}

int __libcpp_condvar_destroy(__libcpp_condvar_t *__cv)
{
  static_cast<void>(__cv);
  return 0;
}

// Execute Once
static_assert(sizeof(__libcpp_exec_once_flag) == sizeof(INIT_ONCE), "incorrect __libcpp_exec_once_flag size");
static_assert(alignof(__libcpp_exec_once_flag) == alignof(INIT_ONCE), "incorrect __libcpp_exec_once_flag alignment");

static inline _LIBCPP_ALWAYS_INLINE BOOL CALLBACK
__libcpp_init_once_execute_once_thunk(PINIT_ONCE __init_once, PVOID __parameter,
                                      PVOID *__context)
{
  static_cast<void>(__init_once);
  static_cast<void>(__context);

  void (*init_routine)(void) = reinterpret_cast<void (*)(void)>(__parameter);
  init_routine();
  return TRUE;
}

int __libcpp_execute_once(__libcpp_exec_once_flag *__flag,
                          void (*__init_routine)(void))
{
  if (!InitOnceExecuteOnce(reinterpret_cast<INIT_ONCE*>(__flag),
                           __libcpp_init_once_execute_once_thunk,
                           reinterpret_cast<void *>(__init_routine), NULL))
    return GetLastError();
  return 0;
}

// Thread ID
bool __libcpp_thread_id_equal(__libcpp_thread_id __lhs,
                              __libcpp_thread_id __rhs)
{
  return __lhs == __rhs;
}

bool __libcpp_thread_id_less(__libcpp_thread_id __lhs, __libcpp_thread_id __rhs)
{
  return __lhs < __rhs;
}

// Thread
static_assert(sizeof(__libcpp_thread_t) == sizeof(HANDLE), "incorrect __libcpp_thread_t size");
static_assert(alignof(__libcpp_thread_t) == alignof(HANDLE), "incorrect __libcpp_thread_t alignment");

struct __libcpp_beginthreadex_thunk_data
{
  void *(*__func)(void *);
  void *__arg;
};

static inline _LIBCPP_ALWAYS_INLINE unsigned WINAPI
__libcpp_beginthreadex_thunk(void *__raw_data)
{
  auto *__data =
      static_cast<__libcpp_beginthreadex_thunk_data *>(__raw_data);
  auto *__func = __data->__func;
  void *__arg = __data->__arg;
  delete __data;
  return static_cast<unsigned>(reinterpret_cast<uintptr_t>(__func(__arg)));
}

bool __libcpp_thread_isnull(const __libcpp_thread_t *__t) {
  return *__t == 0;
}

int __libcpp_thread_create(__libcpp_thread_t *__t, void *(*__func)(void *),
                           void *__arg)
{
  auto *__data = new __libcpp_beginthreadex_thunk_data;
  __data->__func = __func;
  __data->__arg = __arg;

  *__t = static_cast<__libcpp_thread_t>(
      _beginthreadex(nullptr, 0,
                     __libcpp_beginthreadex_thunk,
                     __data, 0, nullptr));

  if (*__t)
    return 0;
  return GetLastError();
}

__libcpp_thread_id __libcpp_thread_get_current_id()
{
  return GetCurrentThreadId();
}

__libcpp_thread_id __libcpp_thread_get_id(const __libcpp_thread_t *__t)
{
  return GetThreadId(reinterpret_cast<HANDLE>(*__t));
}

int __libcpp_thread_join(__libcpp_thread_t *__t)
{
  if (WaitForSingleObjectEx(reinterpret_cast<HANDLE>(*__t), INFINITE, FALSE) == WAIT_FAILED)
    return GetLastError();
  if (!CloseHandle(reinterpret_cast<HANDLE>(*__t)))
    return GetLastError();
  return 0;
}

int __libcpp_thread_detach(__libcpp_thread_t *__t)
{
  if (!CloseHandle(reinterpret_cast<HANDLE>(*__t)))
    return GetLastError();
  return 0;
}

void __libcpp_thread_yield()
{
  SwitchToThread();
}

void __libcpp_thread_sleep_for(const chrono::nanoseconds& __ns)
{
  using namespace chrono;
  // round-up to the nearest milisecond
  milliseconds __ms =
      duration_cast<milliseconds>(__ns + chrono::nanoseconds(999999));
  // FIXME(compnerd) this should be an alertable sleep (WFSO or SleepEx)
  Sleep(__ms.count());
}

// Thread Local Storage
int __libcpp_tls_create(__libcpp_tls_key* __key,
                        void(_LIBCPP_TLS_DESTRUCTOR_CC* __at_exit)(void*))
{
  *__key = FlsAlloc(__at_exit);
  if (*__key == FLS_OUT_OF_INDEXES)
    return GetLastError();
  return 0;
}

void *__libcpp_tls_get(__libcpp_tls_key __key)
{
  return FlsGetValue(__key);
}

int __libcpp_tls_set(__libcpp_tls_key __key, void *__p)
{
  if (!FlsSetValue(__key, __p))
    return GetLastError();
  return 0;
}
_LIBCPP_END_NAMESPACE_STD
