@echo off

REM This command can receive parameters
REM create : means you want to create a new module ;
REM remove : means you want to remove an existing module.

echo Welcome to the SparkEngine module manager.

REM Checking parameters.
if "%1" == "create" goto CreateModule
if "%1" == "remove" goto RemoveModule

goto Failure

:CreateModule
	echo What kind of module do you want to create (lib / app / plugin) :
	set /p ModuleType=

	REM Checking the module type.
	if "%ModuleType%" == "lib" goto CreateLibrary
	if "%ModuleType%" == "app" goto CreateAppplication
	if "%ModuleType%" == "plugin"	goto CreatePlugin
	
	goto ModuleCreationFailure
	
	:CreateLibrary
		REM We have to get some information about the new library
		REM like his name and his target name.
		echo.
		echo Please enter the library name :
		set /p LibraryName=
		pushd src
		if exist %LibraryName% goto ModuleCreationFailure
		
		mkdir %LibraryName%
		pushd %LibraryName%
		
		echo.
		echo Please enter a target name :
		set /p TargetName=
		
		REM Now we have all needed information, we create the CMake file associated.
		echo # ./src/%LibraryName%/CMakeLists.txt>>CMakeLists.txt
		echo. >>CMakeLists.txt
		echo cmake_minimum_required(VERSION 2.8)>>CMakeLists.txt
		echo. >>CMakeLists.txt
		echo project(%LibraryName%)>>CMakeLists.txt
		echo. >>CMakeLists.txt
		echo file(GLOB %LibraryName%_source_file ./*)>>CMakeLists.txt
		echo. >>CMakeLists.txt
		echo add_library(%TargetName% SHARED ${%TargetName%_source_file})>>CMakeLists.txt
		
		REM Now we need to register the new library to the BuildSystem.
		pushd ..\..\
		
		echo add_subdirectory(src/%LibraryName%)>>CMakeLists.txt
		
		popd
		popd
		popd
		
		echo.
		
		goto End
		
	:CreateApplication
	:CreatePlugin
	

	:ModuleCreationFailure
		echo.
		echo An error occured while creating a module.
		popd

	goto End

:RemoveModule
	goto End

:Failure
	echo.
	echo Something wrong happened during the process. Abort !
	
	goto End

:End
	echo Exiting the module manager.