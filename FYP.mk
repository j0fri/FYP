##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=FYP
ConfigurationName      :=Debug
WorkspaceConfiguration :=Debug
WorkspacePath          :=/home/jf1519/FYP/FYP
ProjectPath            :=/home/jf1519/FYP/FYP
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Jordi Frittoli
Date                   :=08/12/22
CodeLitePath           :=/home/jf1519/.codelite
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputDirectory        :=$(IntermediateDirectory)
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="FYP.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -O0
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch). $(LibraryPathSwitch)Debug 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -Wall $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/math_helper.cpp$(ObjectSuffix) $(IntermediateDirectory)/sim.cpp$(ObjectSuffix) $(IntermediateDirectory)/Species.cpp$(ObjectSuffix) $(IntermediateDirectory)/Field.cpp$(ObjectSuffix) $(IntermediateDirectory)/Simulation.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d $(ConfigurationName) || $(MakeDirCommand) $(ConfigurationName)


$(IntermediateDirectory)/.d:
	@test -d $(ConfigurationName) || $(MakeDirCommand) $(ConfigurationName)

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/math_helper.cpp$(ObjectSuffix): math_helper.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/jf1519/FYP/FYP/math_helper.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/math_helper.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/math_helper.cpp$(PreprocessSuffix): math_helper.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/math_helper.cpp$(PreprocessSuffix) math_helper.cpp

$(IntermediateDirectory)/sim.cpp$(ObjectSuffix): sim.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/jf1519/FYP/FYP/sim.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sim.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sim.cpp$(PreprocessSuffix): sim.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sim.cpp$(PreprocessSuffix) sim.cpp

$(IntermediateDirectory)/Species.cpp$(ObjectSuffix): Species.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/jf1519/FYP/FYP/Species.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Species.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Species.cpp$(PreprocessSuffix): Species.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Species.cpp$(PreprocessSuffix) Species.cpp

$(IntermediateDirectory)/Field.cpp$(ObjectSuffix): Field.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/jf1519/FYP/FYP/Field.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Field.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Field.cpp$(PreprocessSuffix): Field.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Field.cpp$(PreprocessSuffix) Field.cpp

$(IntermediateDirectory)/Simulation.cpp$(ObjectSuffix): Simulation.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/jf1519/FYP/FYP/Simulation.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Simulation.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Simulation.cpp$(PreprocessSuffix): Simulation.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Simulation.cpp$(PreprocessSuffix) Simulation.cpp

##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/


