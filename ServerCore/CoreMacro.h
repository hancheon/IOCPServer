#pragma once

#define OUT

//------//
// Lock //
//------//

#define USE_MANY_LOCKS(count)	Lock _locks[count]
#define USE_LOCK				USE_MANY_LOCKS(1)
#define READ_LOCK_IDX(idx)		ReadLockGuard readLockGuard_idx_##(_locks[idx])
#define READ_LOCK				READ_LOCK_IDX(0)
#define WRITE_LOCK_IDX(idx)		WriteLockGuard writeLockGuard_idx_##(_locks[idx])
#define WRITE_LOCK				WRITE_LOCK_IDX(0)

//-------//
// Crash //
//-------//

#define CRASH(cause)								\
do													\
{													\
	uint32* crash = nullptr;						\
	__analysis_assume(crash != nullptr);			\
	* crash = 0xDEABEEF;							\
} while (0)

#define ASSERT_CRASH(expr)							\
do													\
{													\
	if (!(expr))									\
	{												\
		CRASH("ASSERT_CRASH");						\
		__analysis_assume(crash != nullptr);		\
	}												\
} while (0)