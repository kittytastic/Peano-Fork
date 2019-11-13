// Default variant of CompilerSpecificSettings.h for GCC on Windows.
// For a detailed description of the semantics of the settings, please
// consult LinuxIntel.h which is the most elaborate documentation.

//#define UseTestSpecificCompilerSettings

//#define CompilerCLANG
//#define CompilerHasProcStat
//#define CompilerHasUTSName
//#define CompilerHasTimespec
//#define CompilerHasSysinfo
//#define CompilerDefinesMPIMaxNameString


#if !defined(UseManualInlining) &&  !defined(noUseManualInlining)
#define UseManualInlining
#endif

#define LittleEndian
