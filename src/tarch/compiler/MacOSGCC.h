// Default variant of CompilerSpecificSettings.h for GCC on MacOS.
// For a detailed description of the semantics of the settings, please
// consult LinuxIntel.h which is the most elaborate documentation.

/**
 * Switch off Optimisation
 *
 * Some compilers (icc 10.x, e.g.) run into problems compiling the test cases
 * as they run out of memory. In this case, one can use these two defined
 * within the implementation files. Unfortunately, the corresponding pragmas
 * are not supported by all compilers (gcc 4.x.x, e.g.). Therefore, I
 * encapsulated them within my own defines.
 *
 * To make define work, see the documentation of the test super class.
 */
//#define UseTestSpecificCompilerSettings

//#define CompilerCLANG
//#define CompilerICC
//#define CompilerHasProcStat
#define CompilerHasUTSName
#define CompilerHasTimespec
//#define CompilerDefinesMPIMaxNameString
//#define DaStGenPackedPadding 1      // 32 bit version
// #define DaStGenPackedPadding 2   // 64 bit version
//#define CompilerHasSysinfo


#if !defined(noMultipleThreadsMayTriggerMPICalls) && !defined(MultipleThreadsMayTriggerMPICalls)
#define MultipleThreadsMayTriggerMPICalls
#endif


#ifndef SendWorkerMasterMessagesBlocking
 #define SendWorkerMasterMessagesBlocking     0
#endif
#ifndef SendMasterWorkerMessagesBlocking
 #define SendMasterWorkerMessagesBlocking     0
#endif
#ifndef ReceiveMasterMessagesBlocking
 #define ReceiveMasterMessagesBlocking        0
#endif
#ifndef SendAndReceiveLoadBalancingMessagesBlocking
 #define SendAndReceiveLoadBalancingMessagesBlocking    0
#endif
#ifndef ReceiveIterationControlMessagesBlocking
 #define ReceiveIterationControlMessagesBlocking        0
#endif
#ifndef BroadcastToWorkingNodesBlocking
 #define BroadcastToWorkingNodesBlocking                0
#endif
#ifndef SendHeapMetaDataBlocking
 #define SendHeapMetaDataBlocking                       0
#endif
#ifndef SendAndReceiveHeapSynchronousDataBlocking
 #define SendAndReceiveHeapSynchronousDataBlocking      0
#endif



#if !defined(UseManualInlining) &&  !defined(noUseManualInlining)
#define UseManualInlining
#endif

#define LittleEndian

#if !defined(MPIProgressionReliesOnMPITest) &&  !defined(noMPIProgressionReliesOnMPITest)
#define MPIProgressionReliesOnMPITest
#endif

#if !defined(UseTBBsParallelForAndReduce) &&  !defined(noUseTBBsParallelForAndReduce)
#define UseTBBsParallelForAndReduce
#endif

#if defined(MultipleThreadsMayTriggerMPICalls) && !defined(noMPIHeapUsesItsOwnThread) && !defined(MPIHeapUsesItsOwnThread)
#define MPIHeapUsesItsOwnThread
#endif

#if defined(MultipleThreadsMayTriggerMPICalls) && !defined(noMPIUsesItsOwnThread) && !defined(MPIUsesItsOwnThread)
#define MPIUsesItsOwnThread
#endif



#if !defined(BooleanSemaphoreUsesASpinLock) && !defined(noBooleanSemaphoreUsesASpinLock)
#define BooleanSemaphoreUsesASpinLock
#endif

#if !defined(JobQueueUsesSpinLockInsteadOfMutex) && !defined(noJobQueueUsesSpinLockInsteadOfMutex)
#define JobQueueUsesSpinLockInsteadOfMutex
#endif

#if !defined(JobQueueUsesStackOfBefilledQueues) && !defined(noJobQueueUsesStackOfBefilledQueues)
#define JobQueueUsesStackOfBefilledQueues
#endif
