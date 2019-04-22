# Install script for directory: C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/BULLET_PHYSICS")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/bullet" TYPE FILE FILES
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientC_API.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientSharedMemory_C_API.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientSharedMemory2_C_API.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsDirectC_API.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientUDP_C_API.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientTCP_C_API.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/SharedMemoryInProcessPhysicsC_API.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/SharedMemoryPublic.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/b3RobotSimulatorClientAPI_NoGUI.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/b3RobotSimulatorClientAPI_NoDirect.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/bullet_robotics" TYPE FILE FILES
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/Common2dCanvasInterface.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonCallbacks.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonCameraInterface.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonExampleInterface.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonFileIOInterface.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonGraphicsAppInterface.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonGUIHelperInterface.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonMultiBodyBase.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonParameterInterface.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonRenderInterface.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonRigidBodyBase.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/CommonInterfaces/CommonWindowInterface.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/OpenGLWindow/SimpleCamera.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/TinyRenderer/geometry.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/TinyRenderer/model.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/TinyRenderer/tgaimage.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/TinyRenderer/our_gl.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/TinyRenderer/TinyRenderer.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/plugins/collisionFilterPlugin/collisionFilterPlugin.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/plugins/pdControlPlugin/pdControlPlugin.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/b3RobotSimulatorClientAPI_NoGUI.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/b3RobotSimulatorClientAPI_NoDirect.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/IKTrajectoryHelper.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/plugins/tinyRendererPlugin/tinyRendererPlugin.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/plugins/tinyRendererPlugin/TinyRendererVisualShapeConverter.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/InProcessMemory.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsServer.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClient.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsServerSharedMemory.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsDirect.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsDirectC_API.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsServerCommandProcessor.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/b3PluginManager.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientSharedMemory.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientSharedMemory_C_API.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientC_API.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/SharedMemoryPublic.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/Win32SharedMemory.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PosixSharedMemory.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Utils/b3ResourcePath.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Utils/RobotLoggingUtil.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Utils/b3Clock.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Utils/b3ResourcePath.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Utils/ChromeTraceUtil.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Utils/b3ERPCFMHelper.hpp"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Utils/b3ReferenceFrameHelper.hpp"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/tinyxml2/tinyxml2.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/stb_image/stb_image.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/BussIK/Jacobian.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/BussIK/LinearR2.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/BussIK/LinearR3.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/BussIK/LinearR4.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/BussIK/MatrixRmn.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/BussIK/Node.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/BussIK/Tree.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/BussIK/VectorRn.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportColladaDemo/LoadMeshFromCollada.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportObjDemo/LoadMeshFromObj.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportObjDemo/Wavefront2GLInstanceGraphicsShape.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportMJCFDemo/BulletMJCFImporter.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/BulletUrdfImporter.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/MyMultiBodyCreator.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/URDF2Bullet.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/UrdfParser.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/urdfStringSplit.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/URDFImporterInterface.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/URDFJointTypes.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/SDFAudioTypes.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/UrdfRenderingInterface.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportURDFDemo/MultiBodyCreationInterface.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/Importers/ImportMeshUtility/b3ImportMeshUtility.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/MultiThreading/b3PosixThreadSupport.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/MultiThreading/b3Win32ThreadSupport.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/MultiThreading/b3ThreadSupportInterface.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientUDP.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientUDP_C_API.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/enet/include/enet/win32.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/enet/include/enet/unix.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/enet/include/enet/callbacks.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/enet/include/enet/list.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/enet/include/enet/protocol.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientTCP.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/SharedMemory/PhysicsClientTCP_C_API.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/clsocket/src/SimpleSocket.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/clsocket/src/ActiveSocket.h"
    "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bullet3-master/Extras/BulletRobotics/../../examples/ThirdPartyLibs/clsocket/src/PassiveSocket.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bulletbuild/lib/Debug/BulletRobotics_Debug.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bulletbuild/lib/Release/BulletRobotics.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bulletbuild/lib/MinSizeRel/BulletRobotics_MinsizeRel.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/tazd1ngo/Desktop/Advanced Shaders P15232790/OpenGLVS/OpenGLVS/BellfruitGames/include/bulletbuild/lib/RelWithDebInfo/BulletRobotics_RelWithDebugInfo.lib")
  endif()
endif()

