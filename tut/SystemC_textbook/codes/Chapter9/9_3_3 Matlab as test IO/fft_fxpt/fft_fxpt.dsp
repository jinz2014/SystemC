# Microsoft Developer Studio Project File - Name="fft_fxpt" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=fft_fxpt - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "fft_fxpt.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "fft_fxpt.mak" CFG="fft_fxpt - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fft_fxpt - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "fft_fxpt - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "fft_fxpt - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GR /GX /O2 /I "../../../src" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "fft_fxpt - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /I "../../../src" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "fft_fxpt - Win32 Release"
# Name "fft_fxpt - Win32 Debug"
# Begin Source File

SOURCE=..\..\..\examples\systemc\fft\fft_fxpt\fft.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\examples\systemc\fft\fft_fxpt\fft.h
# End Source File
# Begin Source File

SOURCE=.\globals.h
# End Source File
# Begin Source File

SOURCE=E:\MATLAB6p5\extern\lib\win32\microsoft\msvc60\libfixedpoint.exp
# End Source File
# Begin Source File

SOURCE=..\..\..\examples\systemc\fft\fft_fxpt\main.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\examples\systemc\fft\fft_fxpt\sink.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\examples\systemc\fft\fft_fxpt\sink.h
# End Source File
# Begin Source File

SOURCE=..\..\..\examples\systemc\fft\fft_fxpt\source.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\examples\systemc\fft\fft_fxpt\source.h
# End Source File
# Begin Source File

SOURCE=..\..\systemc\Release\systemc.lib
# End Source File
# Begin Source File

SOURCE=E:\MATLAB6p5\extern\lib\win32\microsoft\msvc60\libeng.lib
# End Source File
# Begin Source File

SOURCE=E:\MATLAB6p5\extern\lib\win32\microsoft\msvc60\libfixedpoint.lib
# End Source File
# Begin Source File

SOURCE=E:\MATLAB6p5\extern\lib\win32\microsoft\msvc60\libmat.lib
# End Source File
# Begin Source File

SOURCE=E:\MATLAB6p5\extern\lib\win32\microsoft\msvc60\libmatlb.lib
# End Source File
# Begin Source File

SOURCE=E:\MATLAB6p5\extern\lib\win32\microsoft\msvc60\libmatlbmx.lib
# End Source File
# Begin Source File

SOURCE=E:\MATLAB6p5\extern\lib\win32\microsoft\msvc60\libmex.lib
# End Source File
# Begin Source File

SOURCE=E:\MATLAB6p5\extern\lib\win32\microsoft\msvc60\libmmfile.lib
# End Source File
# Begin Source File

SOURCE=E:\MATLAB6p5\extern\lib\win32\microsoft\msvc60\libmwarpack.lib
# End Source File
# Begin Source File

SOURCE=E:\MATLAB6p5\extern\lib\win32\microsoft\msvc60\libmwlapack.lib
# End Source File
# Begin Source File

SOURCE=E:\MATLAB6p5\extern\lib\win32\microsoft\msvc60\libmwmcl.lib
# End Source File
# Begin Source File

SOURCE=E:\MATLAB6p5\extern\lib\win32\microsoft\msvc60\libmwrefblas.lib
# End Source File
# Begin Source File

SOURCE=E:\MATLAB6p5\extern\lib\win32\microsoft\msvc60\libmwservices.lib
# End Source File
# Begin Source File

SOURCE=E:\MATLAB6p5\extern\lib\win32\microsoft\msvc60\libmwsglm.lib
# End Source File
# Begin Source File

SOURCE=E:\MATLAB6p5\extern\lib\win32\microsoft\msvc60\libmx.lib
# End Source File
# Begin Source File

SOURCE=E:\MATLAB6p5\extern\lib\win32\microsoft\msvc60\libut.lib
# End Source File
# Begin Source File

SOURCE=E:\MATLAB6p5\extern\lib\win32\microsoft\msvc60\mclcommain.lib
# End Source File
# Begin Source File

SOURCE=E:\MATLAB6p5\extern\lib\win32\microsoft\msvc60\sgl.lib
# End Source File
# End Target
# End Project
