cmake_minimum_required(VERSION 3.1)

project(MDL_Workshop)

find_package(OpenGL REQUIRED)

add_library(SMDDocument
    SMDDocument/source/CBase3DDocument.h
    SMDDocument/source/CDataSMD.cpp
    SMDDocument/source/CDataSMD.h
    SMDDocument/source/CSMDDocument.cpp
    SMDDocument/source/CSMDDocument.h
    SMDDocument/source/data_types.h
    )

target_compile_definitions(SMDDocument
    PRIVATE SMDDIALOG_EXPORTS
    )

target_compile_features(SMDDocument
    PRIVATE cxx_nullptr
    )

add_library(MDLDocument
    MDLDocument/hlsdk/activity.h
    MDLDocument/hlsdk/cmdlib.c
    MDLDocument/hlsdk/cmdlib.h
    MDLDocument/hlsdk/mathlib.c
    MDLDocument/hlsdk/mathlib.h
    MDLDocument/hlsdk/studio.h
    MDLDocument/hlsdk/studio_event.h
    MDLDocument/hlsdk/studio_export.cpp
    MDLDocument/hlsdk/studio_import.cpp
    MDLDocument/hlsdk/studio_render.cpp
    MDLDocument/hlsdk/studio_render.h
    MDLDocument/hlsdk/studio_utils.cpp
    MDLDocument/source/CBase3DDocument.h
    MDLDocument/source/CControl.cpp
    MDLDocument/source/CControl.h
    MDLDocument/source/CDialog.cpp
    MDLDocument/source/CDialog.h
    MDLDocument/source/CMDLDocument.cpp
    MDLDocument/source/CMDLDocument.h
    MDLDocument/source/CSequenceDlg.cpp
    MDLDocument/source/CSequenceDlg.h
    MDLDocument/source/CSlider.cpp
    MDLDocument/source/CSlider.h
    MDLDocument/resource/mdl.rc
    source/CBase3DDocument.cpp
    )

target_compile_definitions(MDLDocument
    PRIVATE MDLDIALOG_EXPORTS
    )

target_include_directories(MDLDocument
    PRIVATE MDLDocument/resource
    )

target_compile_features(MDLDocument
    PRIVATE cxx_nullptr
    )

add_executable(MDL_Workshop WIN32
    source/CBase3DDocument.cpp
    source/CBase3DDocument.h
    source/CCommonDialogs.cpp
    source/CCommonDialogs.h
    source/CControl.cpp
    source/CControl.h
    source/CGLCamera.cpp
    source/CGLCamera.h
#    source/CGLWindow.cpp
#    source/CGLWindow.h
    source/CMainFrame.cpp
    source/CMainFrame.h
    source/COpenGL.cpp
    source/COpenGL.h
    source/CRebar.cpp
    source/CRebar.h
    source/CWin.cpp
    source/CWin.h
    source/WinMain.cpp
    resource/app.rc
    resource/resource.h
	)

target_include_directories(MDL_Workshop
    PRIVATE resource
    PRIVATE SMDDocument
    PRIVATE MDLDocument
    )

target_link_libraries(MDL_Workshop
    SMDDocument
    MDLDocument
    ${OPENGL_LIBRARIES}
    comctl32
    winmm
    )

target_compile_features(MDL_Workshop
	PRIVATE cxx_auto_type
	PRIVATE cxx_nullptr
	PRIVATE cxx_range_for
	)
