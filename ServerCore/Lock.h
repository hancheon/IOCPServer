#pragma once

//-------------//
// RW SpinLock //
//-------------//
//-------------------------------------------------------------------
// [WWWW'WWWW][WWWW'WWWW] \ [RRRR'RRRR][RRRR'RRRR]
// WriteFlag (Upper 16bits)	: Exclusive Lock Ownder Thread Id
// ReadFlag (Lower 16bits)	: Shared Lock Count
// 
// Same Thread...
// Write Lock -> Get Read Lock [O]
// Read Lock -> Get Write Lock [X]
// 
// _writeCount: Recursive Lock Count
//-------------------------------------------------------------------

class Lock
{
	enum : uint32
	{
		ACQUIRE_TIMEOUT_TICK	= 10000,
		MAX_SPIN_COUNT			= 5000,
		WRITE_THREAD_MASK		= 0xFFFF'0000,
		READ_COUNT_MASK			= 0x0000'FFFF,
		EMPTY_FLAG				= 0x0000'0000,
	};

public:
	void WriteLock();
	void WriteUnlock();
	void ReadLock();
	void ReadUnlock();

private:
	Atomic<uint32>	_lockFlag;
	uint16			_writeCount;
};

//------------//
// Lock Guard //
//------------//

class ReadLockGuard
{
public:
	ReadLockGuard(Lock& lock) : _lock(lock) { _lock.ReadLock(); }
	~ReadLockGuard() { _lock.ReadUnlock(); }

private:
	Lock& _lock;
};

class WriteLockGuard
{
public:
	WriteLockGuard(Lock& lock) : _lock(lock) { _lock.WriteLock(); }
	~WriteLockGuard() { _lock.WriteUnlock(); }

private:
	Lock& _lock;
};