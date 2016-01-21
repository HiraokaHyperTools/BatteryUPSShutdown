 // ***** Sample.mc *****
 // This is the header section.
 // The following are message definitions.
//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_SYSTEM                  0x0
#define FACILITY_STUBS                   0x3
#define FACILITY_RUNTIME                 0x2
#define FACILITY_IO_ERROR_CODE           0x4


//
// Define the severity codes
//
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_ERROR            0x3


//
// MessageId: MSG_UPS_TIMER1_STARTED
//
// MessageText:
//
//  Primary timer started. It counts on shutdown notice.
//
#define MSG_UPS_TIMER1_STARTED           ((DWORD)0x00020001L)

//
// MessageId: MSG_UPS_TIMER1_FAILED
//
// MessageText:
//
//  Primary timer failed to start.
//
#define MSG_UPS_TIMER1_FAILED            ((DWORD)0x80020002L)

//
// MessageId: MSG_UPS_CMDLINE_LAUNCHED
//
// MessageText:
//
//  Command line launched: %1
//
#define MSG_UPS_CMDLINE_LAUNCHED         ((DWORD)0x00020002L)

//
// MessageId: MSG_UPS_CMDLINE_FAILED
//
// MessageText:
//
//  Command line failed to launch: %1
//
#define MSG_UPS_CMDLINE_FAILED           ((DWORD)0x80020003L)

//
// MessageId: MSG_UPS_SHUTDOWN_INITED
//
// MessageText:
//
//  Shutdown notice initiated, PC: %1
//
#define MSG_UPS_SHUTDOWN_INITED          ((DWORD)0x00020004L)

//
// MessageId: MSG_UPS_SHUTDOWN_FAILED
//
// MessageText:
//
//  Shutdown notice failed, PC: %1 (%2)
//
#define MSG_UPS_SHUTDOWN_FAILED          ((DWORD)0x80020005L)

