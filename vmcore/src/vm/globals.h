/*
 * Copyright 2004-2010 Sun Microsystems, Inc. All Rights Reserved.
 * Copyright 2011 Oracle Corporation. All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER
 *
 * This code is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * only, as published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License version 2 for more details (a copy is
 * included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with this work; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 * Please contact Oracle Corporation, 500 Oracle Parkway, Redwood
 * Shores, CA 94065 or visit www.oracle.com if you need additional
 * information or have any questions.
 */

#define MAX_STREAMS 4

#if (defined(ASSUME) && ASSUME != 0) | TRACE
#define INTERPRETER_STATS 1
#endif /* ASSUME */

/**
 * This struct encapsulates all the globals in the Squawk VM. This allows
 * a system to be built with several separate VM execution contexts.
 */
typedef struct globalsStruct {
    Address     _memory;                     /* The buffer containing ROM, NVM, RAM and serviceChunk */
    Address     _memoryEnd;                  /* The end of the memory buffer. */
    UWord       _memorySize;                 /* The size (in bytes) of the memory buffer. */

#ifndef MACROIZE
    int          _iparm;                     /* The immediate operand value of the current bytecode. */
    ByteAddress  _ip;                        /* The instruction pointer. */
    UWordAddress _fp;                        /* The frame pointer. */
    UWordAddress _sp;                        /* The stack pointer. */
#else
#if TRACE
    ByteAddress  _lastIP;
    UWordAddress _lastFP;
#endif /* TRACE */
#endif /* MACROIZE */

    UWordAddress _sl;                        /* The stack limit. */
    UWordAddress _ss;                        /* The stack start. */
    int          _bc;                        /* The branch counter. */

    ByteAddress  _saved_ip;                  /* The saved instruction pointer. */
    UWordAddress _saved_fp;                  /* The saved frame pointer. */
    UWordAddress _saved_sp;                  /* The saved stack pointer. */

    int         _Ints[GLOBAL_INT_COUNT];     /* Storage for the primitive typed Java globals. */
    Address     _Addrs[GLOBAL_ADDR_COUNT];   /* Storage for the primitive typed Java globals. */
    Address     _Oops[GLOBAL_OOP_COUNT];     /* Storage for the reference typed Java globals. */
    Address     _Buffers[MAX_BUFFERS];       /* Buffers that are allocated by native code. */
    int         _BufferCount;                /* Number of buffers that are currently allocated by native code. */
    FILE       *_streams[MAX_STREAMS];       /* The file streams to which the VM printing directives sent. */
    int         _currentStream;              /* The currently selected stream */
    int         _internalLowResult;          /* Value for INTERNAL_LOW_RESULT */

    void*       _nativeFuncPtr;               /* Ptr to the function that is being called via NativeUnsafe.call, or null */

#ifdef PROFILING
    int         _sampleFrequency;            /* The profile sample frequency */
    jlong       _instructionCount;
#endif /* PROFILING */

#if TRACE
    FILE       *_traceFile;                  /* The trace file name */
    boolean     _traceFileOpen;              /* Specifies if the trace file has been opened. */
    boolean     _traceServiceThread;         /* Specifies if execution on the service thread is to be traced. */
    int         _traceLastThreadID;          /* Specifies the thread ID at the last call to trace() */
    
    int         _total_extends;              /* Total number of extends */
    int         _total_slots;                /* Total number of slots cleared */
    
    int         _statsFrequency;             /* The statistics output frequency */
#endif /* TRACE */

#if defined(PROFILING) | TRACE
    jlong       _lastStatCount;
#endif /* PROFILING */

    Address     _cachedClassState[CLASS_CACHE_SIZE > 0 ? CLASS_CACHE_SIZE : 1];
    Address     _cachedClass     [CLASS_CACHE_SIZE > 0 ? CLASS_CACHE_SIZE : 1];
#ifdef INTERPRETER_STATS
    int         _cachedClassAccesses;
    int         _cachedClassHits;
#endif /* INTERPRETER_STATS */

    Address    *_pendingMonitors;
    int         _pendingMonitorStackPointer;
#ifdef INTERPRETER_STATS
    int         _pendingMonitorAccesses;
    int         _pendingMonitorHits;
#endif /* INTERPRETER_STATS */

} Globals;


/*=======================================================================*\
 *                          Truly global globals                         *
\*=======================================================================*/

Globals *gp;              /* The pointer to the global execution context */
Globals userGlobals;      /* The user mode execution context */

#define defineGlobal(x) userGlobals._##x

#define defineGlobalContext(c,x) c._##x

int         interruptsDisabled;         /* Depth-count:  for correct interrupt state changes */

boolean     notrap;

/*=======================================================================*\
 *                             Virtual globals                           *
\*=======================================================================*/

#define memory                              defineGlobal(memory)
#define memoryEnd                           defineGlobal(memoryEnd)
#define memorySize                          defineGlobal(memorySize)

#ifndef MACROIZE
#define iparm                               defineGlobal(iparm)
#define ip                                  defineGlobal(ip)
#define fp                                  defineGlobal(fp)
#define sp                                  defineGlobal(sp)
#else
#if TRACE
#define lastIP                              defineGlobal(lastIP)
#define lastFP                              defineGlobal(lastFP)
#endif /* TRACE */
#endif /* MACROIZE */

#define saved_ip                            defineGlobal(saved_ip)
#define saved_fp                            defineGlobal(saved_fp)
#define saved_sp                            defineGlobal(saved_sp)

#define sl                                  defineGlobal(sl)
#define ss                                  defineGlobal(ss)
#define bc                                  defineGlobal(bc)
#define internalLowResult                   defineGlobal(internalLowResult)
#define Ints                                defineGlobal(Ints)
#define Addrs                               defineGlobal(Addrs)
#define Oops                                defineGlobal(Oops)
#define Buffers                             defineGlobal(Buffers)
#define BufferCount                         defineGlobal(BufferCount)

#define cachedClassState                    defineGlobal(cachedClassState)
#define cachedClass                         defineGlobal(cachedClass)
#ifdef INTERPRETER_STATS
#define cachedClassAccesses                 defineGlobal(cachedClassAccesses)
#define cachedClassHits                     defineGlobal(cachedClassHits)
#endif /* INTERPRETER_STATS */

#define pendingMonitors                     defineGlobal(pendingMonitors)
#define pendingMonitorStackPointer          defineGlobal(pendingMonitorStackPointer)
#ifdef INTERPRETER_STATS
#define pendingMonitorAccesses              defineGlobal(pendingMonitorAccesses)
#define pendingMonitorHits                  defineGlobal(pendingMonitorHits)
#endif /* INTERPRETER_STATS */

#define streams                             defineGlobal(streams)
#define currentStream                       defineGlobal(currentStream)

#define nativeFuncPtr                       defineGlobal(nativeFuncPtr)

#define STREAM_COUNT                        (sizeof(Streams) / sizeof(FILE*))

#if TRACE
#define traceFile                           defineGlobal(traceFile)
#define traceFileOpen                       defineGlobal(traceFileOpen)
#define traceServiceThread                  defineGlobal(traceServiceThread)
#define traceLastThreadID                   defineGlobal(traceLastThreadID)
#define setLongCounter(high, low, x)        { high = (int)(x >> 32); low = (int)(x);}
#define getLongCounter(high, low)           ((((ujlong)(unsigned)high) << 32) | ((unsigned)low))
#define getBranchCount()                    getLongCounter(branchCountHigh, branchCountLow)
#define getTraceStart()                     getLongCounter(traceStartHigh, traceStartLow)
#define getTraceEnd()                       getLongCounter(traceEndHigh, traceEndLow)
#define setTraceStart(x)                    setLongCounter(traceStartHigh, traceStartLow, (x)); if ((x) == 0) { com_sun_squawk_VM_tracing = true; }
#define setTraceEnd(x)                      setLongCounter(traceEndHigh, traceEndLow, (x))
#define statsFrequency                      defineGlobal(statsFrequency)
#define total_extends                       defineGlobal(total_extends)
#define total_slots                         defineGlobal(total_slots)
#else
#define getBranchCount()                    ((jlong)-1L)
#endif /* TRACE */

#ifdef PROFILING
#define sampleFrequency                     defineGlobal(sampleFrequency)
#define instructionCount                    defineGlobal(instructionCount)
#endif /* PROFILING */

#if defined(PROFILING) | TRACE
#define lastStatCount                       defineGlobal(lastStatCount)
#endif /* PROFILING */
    
/**
 * Initialize/re-initialize the globals to their defaults.
 */
int initializeGlobals(Globals *globals) {
    gp = globals;
    memset(gp, 0, sizeof(Globals));

    /*
     * Initialize the variables that have non-zero defaults.
     */
    com_sun_squawk_VM_extendsEnabled = true;
    interruptsDisabled = 0;      /* enabled by default */
    runningOnServiceThread = true;
    pendingMonitors = &Oops[ROM_GLOBAL_OOP_COUNT];

    streams[com_sun_squawk_VM_STREAM_STDOUT] = stdout;
    streams[com_sun_squawk_VM_STREAM_STDERR] = stderr;
    currentStream = com_sun_squawk_VM_STREAM_STDERR;

#if TRACE
    setTraceStart(TRACESTART);
    setTraceEnd(TRACESTART);
    traceLastThreadID = -2;
    traceServiceThread = true;
#endif /* TRACE */

    return 0;
}

/**
 * Prints the name and current value of all the globals.
 */
void printGlobals() {
    FILE *vmOut = streams[currentStream];
#if TRACE
    int i;

    // Print the global integers
    fprintf(vmOut, "Global ints:\n");
    for (i = 0; i != GLOBAL_INT_COUNT; ++i) {
        fprintf(vmOut, "  %s = %d\n", getGlobalIntName(i), Ints[i]);
    }

    // Print the global oops
    fprintf(vmOut, "Global oops:\n");
    for (i = 0; i != GLOBAL_OOP_COUNT; ++i) {
        fprintf(vmOut, format("  %s = %A\n"), getGlobalOopName(i), Oops[i]);
    }

    // Print the global addresses
    fprintf(vmOut, "Global addresses:\n");
    for (i = 0; i != GLOBAL_ADDR_COUNT; ++i) {
        fprintf(vmOut, format("  %s = %A\n"), getGlobalAddrName(i), Addrs[i]);
    }
#else
    fprintf(vmOut, "printGlobals() requires tracing\n");
#endif /* TRACE */
}

/**
 * Sets the stream for the VM.print... methods to one of the com_sun_squawk_VM_STREAM_... constants.
 *
 * @param stream  the stream to use for the print... methods
 * @return the current stream used for VM printing
 *
 * @vm2c proxy( setStream )
 */
int setStream(int stream) {
    int result = currentStream;
    currentStream = stream;
    if (streams[currentStream] == null) {
        switch (currentStream) {
#if com_sun_squawk_Klass_ENABLE_DYNAMIC_CLASSLOADING
            case com_sun_squawk_VM_STREAM_SYMBOLS: {
                streams[currentStream] = fopen("squawk_dynamic.sym", "w");
                break;
            }
#endif /* ENABLE_DYNAMIC_CLASSLOADING */
            default: {
                NORETURN void fatalVMError(char *msg);
                fatalVMError("Bad INTERNAL_SETSTREAM");
            }
        }
    }
    return result;
}

/**
 * Closes all the open files used for VM printing.
 */
void finalizeStreams() {
    int i;
    for (i = 0 ; i < MAX_STREAMS ; i++) {
        FILE *file = streams[i];
        if (file != null) {
            fflush(file);
            if (file != stdout && file != stderr) {
                fclose(file);
            }
        }
    }
}

/* These macros are useful for recording the current context
 * (e.g., user or kernel) in a data structure such as a message.
 */
#define setContext(v, t)           (v = (t)gp)
#define isCurrentContext(v, t)     ((v) == (t)gp)


typedef int (*funcPtr0)();
typedef int (*funcPtr1)(int);
typedef int (*funcPtr2)(int, int); 
typedef int (*funcPtr3)(int, int, int); 
typedef int (*funcPtr4)(int, int, int, int);
typedef int (*funcPtr5)(int, int, int, int, int); 
typedef int (*funcPtr6)(int, int, int, int, int, int);
typedef int (*funcPtr7)(int, int, int, int, int, int, int);
typedef int (*funcPtr8)(int, int, int, int, int, int, int, int);
typedef int (*funcPtr9)(int, int, int, int, int, int, int, int, int);
typedef int (*funcPtr10)(int, int, int, int, int, int, int, int, int, int);


