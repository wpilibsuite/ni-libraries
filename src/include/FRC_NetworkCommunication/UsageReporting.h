
#ifndef __UsageReporting_h__
#define __UsageReporting_h__

#ifdef _WIN32
#include <stdint.h>
#define EXPORT_FUNC __declspec(dllexport) __cdecl
#elif defined(__vxworks)
#include <vxWorks.h>
#define EXPORT_FUNC
#else
#include <stdint.h>
#include <stdlib.h>
#define EXPORT_FUNC
#endif

#define kUsageReporting_version 1

namespace nUsageReporting
{
typedef enum
{
    kResourceType_Controller,
    kResourceType_Module,
    kResourceType_Language,
    kResourceType_CANPlugin,
    kResourceType_Accelerometer,
    kResourceType_ADXL345,
    kResourceType_AnalogChannel,
    kResourceType_AnalogTrigger,
    kResourceType_AnalogTriggerOutput,
    kResourceType_CANJaguar,
    kResourceType_Compressor, // 10
    kResourceType_Counter,
    kResourceType_Dashboard,
    kResourceType_DigitalInput,
    kResourceType_DigitalOutput,
    kResourceType_DriverStationCIO,
    kResourceType_DriverStationEIO,
    kResourceType_DriverStationLCD,
    kResourceType_Encoder,
    kResourceType_GearTooth,
    kResourceType_Gyro, // 20
    kResourceType_I2C,
    kResourceType_Framework,
    kResourceType_Jaguar,
    kResourceType_Joystick,
    kResourceType_Kinect,
    kResourceType_KinectStick,
    kResourceType_PIDController,
    kResourceType_Preferences,
    kResourceType_PWM,
    kResourceType_Relay, // 30
    kResourceType_RobotDrive,
    kResourceType_SerialPort,
    kResourceType_Servo,
    kResourceType_Solenoid,
    kResourceType_SPI,
    kResourceType_Task,
    kResourceType_Ultrasonic,
    kResourceType_Victor,
    kResourceType_Button,
    kResourceType_Command, // 40
    kResourceType_AxisCamera,
    kResourceType_PCVideoServer,
    kResourceType_SmartDashboard,
    kResourceType_Talon,
    kResourceType_HiTechnicColorSensor,
    kResourceType_HiTechnicAccel,
    kResourceType_HiTechnicCompass,
    kResourceType_SRF08,
    kResourceType_AnalogOutput,
    kResourceType_VictorSP, // 50
    kResourceType_PWMTalonSRX,
    kResourceType_CANTalonSRX,
    kResourceType_ADXL362,
    kResourceType_ADXRS450,
    kResourceType_RevSPARK,
    kResourceType_MindsensorsSD540,
    kResourceType_DigitalGlitchFilter,
    kResourceType_ADIS16448,
    kResourceType_PDP,
    kResourceType_PCM, // 60
    kResourceType_PigeonIMU,
    kResourceType_NidecBrushless,
    kResourceType_CANifier,
    kResourceType_TalonFX,
    kResourceType_CTRE_future1,
    kResourceType_CTRE_future2,
    kResourceType_CTRE_future3,
    kResourceType_CTRE_future4,
    kResourceType_CTRE_future5,
    kResourceType_CTRE_future6, // 70
    kResourceType_LinearFilter,
    kResourceType_XboxController,
    kResourceType_UsbCamera,
    kResourceType_NavX,
    kResourceType_Pixy,
    kResourceType_Pixy2,
    kResourceType_ScanseSweep,
    kResourceType_Shuffleboard,
    kResourceType_CAN,
    kResourceType_DigilentDMC60, // 80
    kResourceType_PWMVictorSPX,
    kResourceType_RevSparkMaxPWM,
    kResourceType_RevSparkMaxCAN,
    kResourceType_ADIS16470,
    kResourceType_PIDController2,
    kResourceType_ProfiledPIDController,
    kResourceType_Kinematics,
    kResourceType_Odometry,
    kResourceType_Units,
    kResourceType_TrapezoidProfile, // 90
    kResourceType_DutyCycle,
    kResourceType_AddressableLEDs,
    kResourceType_FusionVenom,
    kResourceType_CTRE_future7,
    kResourceType_CTRE_future8,
    kResourceType_CTRE_future9,
    kResourceType_CTRE_future10,
    kResourceType_CTRE_future11,
    kResourceType_CTRE_future12,
    kResourceType_CTRE_future13, // 100
    kResourceType_CTRE_future14,
    kResourceType_ExponentialProfile,
    kResourceType_PS4Controller,
    kResourceType_PhotonCamera,
    kResourceType_PhotonPoseEstimator,
    kResourceType_PathPlannerPath,
    kResourceType_PathPlannerAuto,
    kResourceType_PathFindingCommand,
    kResourceType_Redux_future1,
    kResourceType_Redux_future2, // 110
    kResourceType_Redux_future3,
    kResourceType_Redux_future4,
    kResourceType_Redux_future5,
    kResourceType_RevSparkFlexCAN,
    kResourceType_RevSparkFlexPWM,
    kResourceType_WPIlib_future1,
    kResourceType_WPIlib_future2,
    kResourceType_WPIlib_future3,
    kResourceType_WPIlib_future4,
    kResourceType_WPIlib_future5, // 120
    kResourceType_WPIlib_future6,
    kResourceType_WPIlib_future7,
    kResourceType_WPIlib_future8,
    kResourceType_Rev_ServoHub,

//    kResourceType_MaximumID = 255,
} tResourceType;

typedef enum
{
    kLanguage_LabVIEW = 1,
    kLanguage_CPlusPlus = 2,
    kLanguage_Java = 3,
    kLanguage_Python = 4,
    kLanguage_DotNet = 5,
    kLanguage_Kotlin = 6,

    kCANPlugin_BlackJagBridge = 1,
    kCANPlugin_2CAN = 2,

    kFramework_Iterative = 1,
    kFramework_Simple = 2,
    kFramework_CommandControl = 3,
    kFramework_Timed = 4,
    kFramework_ROS = 5,
    kFramework_RobotBuilder = 6,
    kFramework_AdvantageKit = 7,

    kRobotDrive_ArcadeStandard = 1,
    kRobotDrive_ArcadeButtonSpin = 2,
    kRobotDrive_ArcadeRatioCurve = 3,
    kRobotDrive_Tank = 4,
    kRobotDrive_MecanumPolar = 5,
    kRobotDrive_MecanumCartesian = 6,
    kRobotDrive2_DifferentialArcade = 7,
    kRobotDrive2_DifferentialTank = 8,
    kRobotDrive2_DifferentialCurvature = 9,
    kRobotDrive2_MecanumCartesian = 10,
    kRobotDrive2_MecanumPolar = 11,
    kRobotDrive2_KilloughCartesian = 12,
    kRobotDrive2_KilloughPolar = 13,

    kDriverStationCIO_Analog = 1,
    kDriverStationCIO_DigitalIn = 2,
    kDriverStationCIO_DigitalOut = 3,

    kDriverStationEIO_Acceleration = 1,
    kDriverStationEIO_AnalogIn = 2,
    kDriverStationEIO_AnalogOut = 3,
    kDriverStationEIO_Button = 4,
    kDriverStationEIO_LED = 5,
    kDriverStationEIO_DigitalIn = 6,
    kDriverStationEIO_DigitalOut = 7,
    kDriverStationEIO_FixedDigitalOut = 8,
    kDriverStationEIO_PWM = 9,
    kDriverStationEIO_Encoder = 10,
    kDriverStationEIO_TouchSlider = 11,

    kADXL345_SPI = 1,
    kADXL345_I2C = 2,

    kCommand_Scheduler = 1,
    kCommand2_Scheduler = 2,

    kSmartDashboard_Instance = 1,

    kKinematics_DifferentialDrive = 1,
    kKinematics_MecanumDrive = 2,
    kKinematics_SwerveDrive = 3,

    kOdometry_DifferentialDrive = 1,
    kOdometry_MecanumDrive = 2,
    kOdometry_SwerveDrive = 3,
} tInstances;

/**
 * Report the usage of a resource of interest.
 *
 * @param resource one of the values in the tResourceType above (max value 51).
 * @param instanceNumber an index that identifies the resource instance.
 * @param context an optional additional context number for some cases (such as module number).  Set to 0 to omit.
 * @param feature a string to be included describing features in use on a specific resource.  Setting the same resource more than once allows you to change the feature string.
 */
uint32_t EXPORT_FUNC report(tResourceType resource, uint8_t instanceNumber, uint8_t context = 0, const char* feature = NULL);
} // namespace nUsageReporting

#ifdef __cplusplus
extern "C"
{
#endif

    uint32_t EXPORT_FUNC FRC_NetworkCommunication_nUsageReporting_report(uint8_t resource, uint8_t instanceNumber, uint8_t context, const char* feature);

#ifdef __cplusplus
}
#endif

#endif // __UsageReporting_h__
