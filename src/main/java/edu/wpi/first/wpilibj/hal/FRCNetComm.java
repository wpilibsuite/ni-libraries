/*----------------------------------------------------------------------------*/
/* Copyright (c) 2016-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// Autogenerated by wpilibj_frcnetcomm.py. Do not manually edit this file.

package edu.wpi.first.wpilibj.hal;

/**
 * JNI wrapper for library <b>FRC_NetworkCommunication</b><br>.
 */
@SuppressWarnings({"MethodName", "LineLength"})
public class FRCNetComm {
  /**
   * Module type from LoadOut.h
   */
  @SuppressWarnings({"TypeName", "PMD.ConstantsInInterface"})
  public static final class tModuleType {
    private tModuleType() {
    }

    public static final int kModuleType_Unknown = 0x00;
    public static final int kModuleType_Analog = 0x01;
    public static final int kModuleType_Digital = 0x02;
    public static final int kModuleType_Solenoid = 0x03;
  }

  /**
   * Target class from LoadOut.h
   */
  @SuppressWarnings({"TypeName", "PMD.ConstantsInInterface"})
  public static final class tTargetClass {
    private tTargetClass() {
    }

    public static final int kTargetClass_Unknown = 0x00;
    public static final int kTargetClass_FRC1 = 0x10;
    public static final int kTargetClass_FRC2 = 0x20;
    public static final int kTargetClass_FRC3 = 0x30;
    public static final int kTargetClass_RoboRIO = 0x40;
    public static final int kTargetClass_FRC2_Analog = kTargetClass_FRC2 | tModuleType.kModuleType_Analog;
    public static final int kTargetClass_FRC2_Digital = kTargetClass_FRC2 | tModuleType.kModuleType_Digital;
    public static final int kTargetClass_FRC2_Solenoid = kTargetClass_FRC2 | tModuleType.kModuleType_Solenoid;
    public static final int kTargetClass_FamilyMask = 0xF0;
    public static final int kTargetClass_ModuleMask = 0x0F;
  }

  /**
   * Resource type from UsageReporting.h
   */
  @SuppressWarnings({"TypeName", "PMD.ConstantsInInterface"})
  public static final class tResourceType {
    private tResourceType() {
    }

    public static final int kResourceType_Controller = 0;
    public static final int kResourceType_Module = 1;
    public static final int kResourceType_Language = 2;
    public static final int kResourceType_CANPlugin = 3;
    public static final int kResourceType_Accelerometer = 4;
    public static final int kResourceType_ADXL345 = 5;
    public static final int kResourceType_AnalogChannel = 6;
    public static final int kResourceType_AnalogTrigger = 7;
    public static final int kResourceType_AnalogTriggerOutput = 8;
    public static final int kResourceType_CANJaguar = 9;
    public static final int kResourceType_Compressor = 10;
    public static final int kResourceType_Counter = 11;
    public static final int kResourceType_Dashboard = 12;
    public static final int kResourceType_DigitalInput = 13;
    public static final int kResourceType_DigitalOutput = 14;
    public static final int kResourceType_DriverStationCIO = 15;
    public static final int kResourceType_DriverStationEIO = 16;
    public static final int kResourceType_DriverStationLCD = 17;
    public static final int kResourceType_Encoder = 18;
    public static final int kResourceType_GearTooth = 19;
    public static final int kResourceType_Gyro = 20;
    public static final int kResourceType_I2C = 21;
    public static final int kResourceType_Framework = 22;
    public static final int kResourceType_Jaguar = 23;
    public static final int kResourceType_Joystick = 24;
    public static final int kResourceType_Kinect = 25;
    public static final int kResourceType_KinectStick = 26;
    public static final int kResourceType_PIDController = 27;
    public static final int kResourceType_Preferences = 28;
    public static final int kResourceType_PWM = 29;
    public static final int kResourceType_Relay = 30;
    public static final int kResourceType_RobotDrive = 31;
    public static final int kResourceType_SerialPort = 32;
    public static final int kResourceType_Servo = 33;
    public static final int kResourceType_Solenoid = 34;
    public static final int kResourceType_SPI = 35;
    public static final int kResourceType_Task = 36;
    public static final int kResourceType_Ultrasonic = 37;
    public static final int kResourceType_Victor = 38;
    public static final int kResourceType_Button = 39;
    public static final int kResourceType_Command = 40;
    public static final int kResourceType_AxisCamera = 41;
    public static final int kResourceType_PCVideoServer = 42;
    public static final int kResourceType_SmartDashboard = 43;
    public static final int kResourceType_Talon = 44;
    public static final int kResourceType_HiTechnicColorSensor = 45;
    public static final int kResourceType_HiTechnicAccel = 46;
    public static final int kResourceType_HiTechnicCompass = 47;
    public static final int kResourceType_SRF08 = 48;
    public static final int kResourceType_AnalogOutput = 49;
    public static final int kResourceType_VictorSP = 50;
    public static final int kResourceType_PWMTalonSRX = 51;
    public static final int kResourceType_CANTalonSRX = 52;
    public static final int kResourceType_ADXL362 = 53;
    public static final int kResourceType_ADXRS450 = 54;
    public static final int kResourceType_RevSPARK = 55;
    public static final int kResourceType_MindsensorsSD540 = 56;
    public static final int kResourceType_DigitalGlitchFilter = 57;
    public static final int kResourceType_ADIS16448 = 58;
    public static final int kResourceType_PDP = 59;
    public static final int kResourceType_PCM = 60;
    public static final int kResourceType_PigeonIMU = 61;
    public static final int kResourceType_NidecBrushless = 62;
    public static final int kResourceType_CANifier = 63;
    public static final int kResourceType_CTRE_future0 = 64;
    public static final int kResourceType_CTRE_future1 = 65;
    public static final int kResourceType_CTRE_future2 = 66;
    public static final int kResourceType_CTRE_future3 = 67;
    public static final int kResourceType_CTRE_future4 = 68;
    public static final int kResourceType_CTRE_future5 = 69;
    public static final int kResourceType_CTRE_future6 = 70;
    public static final int kResourceType_LinearFilter = 71;
    public static final int kResourceType_XboxController = 72;
    public static final int kResourceType_UsbCamera = 73;
    public static final int kResourceType_NavX = 74;
    public static final int kResourceType_Pixy = 75;
    public static final int kResourceType_Pixy2 = 76;
    public static final int kResourceType_ScanseSweep = 77;
    public static final int kResourceType_Shuffleboard = 78;
    public static final int kResourceType_CAN = 79;
    public static final int kResourceType_DigilentDMC60 = 80;
    public static final int kResourceType_PWMVictorSPX = 81;
  }

  /**
   * Instances from UsageReporting.h
   */
  @SuppressWarnings({"TypeName", "PMD.ConstantsInInterface"})
  public static final class tInstances {
    private tInstances() {
    }

    public static final int kLanguage_LabVIEW = 1;
    public static final int kLanguage_CPlusPlus = 2;
    public static final int kLanguage_Java = 3;
    public static final int kLanguage_Python = 4;
    public static final int kLanguage_DotNet = 5;
    public static final int kCANPlugin_BlackJagBridge = 1;
    public static final int kCANPlugin_2CAN = 2;
    public static final int kFramework_Iterative = 1;
    public static final int kFramework_Simple = 2;
    public static final int kFramework_CommandControl = 3;
    public static final int kFramework_Timed = 4;
    public static final int kFramework_ROS = 5;
    public static final int kFramework_RobotBuilder = 6;
    public static final int kRobotDrive_ArcadeStandard = 1;
    public static final int kRobotDrive_ArcadeButtonSpin = 2;
    public static final int kRobotDrive_ArcadeRatioCurve = 3;
    public static final int kRobotDrive_Tank = 4;
    public static final int kRobotDrive_MecanumPolar = 5;
    public static final int kRobotDrive_MecanumCartesian = 6;
    public static final int kRobotDrive2_DifferentialArcade = 7;
    public static final int kRobotDrive2_DifferentialTank = 8;
    public static final int kRobotDrive2_DifferentialCurvature = 9;
    public static final int kRobotDrive2_MecanumCartesian = 10;
    public static final int kRobotDrive2_MecanumPolar = 11;
    public static final int kRobotDrive2_KilloughCartesian = 12;
    public static final int kRobotDrive2_KilloughPolar = 13;
    public static final int kDriverStationCIO_Analog = 1;
    public static final int kDriverStationCIO_DigitalIn = 2;
    public static final int kDriverStationCIO_DigitalOut = 3;
    public static final int kDriverStationEIO_Acceleration = 1;
    public static final int kDriverStationEIO_AnalogIn = 2;
    public static final int kDriverStationEIO_AnalogOut = 3;
    public static final int kDriverStationEIO_Button = 4;
    public static final int kDriverStationEIO_LED = 5;
    public static final int kDriverStationEIO_DigitalIn = 6;
    public static final int kDriverStationEIO_DigitalOut = 7;
    public static final int kDriverStationEIO_FixedDigitalOut = 8;
    public static final int kDriverStationEIO_PWM = 9;
    public static final int kDriverStationEIO_Encoder = 10;
    public static final int kDriverStationEIO_TouchSlider = 11;
    public static final int kADXL345_SPI = 1;
    public static final int kADXL345_I2C = 2;
    public static final int kCommand_Scheduler = 1;
    public static final int kSmartDashboard_Instance = 1;
  }
}
