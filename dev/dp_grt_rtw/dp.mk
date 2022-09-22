###########################################################################
## Makefile generated for component 'dp'. 
## 
## Makefile     : dp.mk
## Generated on : Thu Sep 22 10:40:13 2022
## Final product: $(RELATIVE_PATH_TO_ANCHOR)/dp
## Product type : executable
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile

PRODUCT_NAME              = dp
MAKEFILE                  = dp.mk
MATLAB_ROOT               = /usr/local/MATLAB/R2022b
MATLAB_BIN                = /usr/local/MATLAB/R2022b/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/glnxa64
START_DIR                 = /home/smerx/git/vtol/dev
SOLVER                    = 
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
TGT_FCN_LIB               = ISO_C
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 0
RELATIVE_PATH_TO_ANCHOR   = ..
C_STANDARD_OPTS           = -fwrapv
CPP_STANDARD_OPTS         = -fwrapv
LIBSSC_SLI_STD_OBJS       = 
LIBSM_SSCI_STD_OBJS       = 
LIBSSC_CORE_STD_OBJS      = 
LIBSSC_ST_STD_OBJS        = 
LIBMC_STD_OBJS            = 
LIBSM_STD_OBJS            = 
LIBPM_MATH_STD_OBJS       = 
LIBPM_STD_OBJS            = 

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          GNU gcc/g++ | gmake (64-bit Linux)
# Supported Version(s):    
# ToolchainInfo Version:   2022b
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# C_STANDARD_OPTS
# CPP_STANDARD_OPTS

#-----------
# MACROS
#-----------

WARN_FLAGS         = -Wall -W -Wwrite-strings -Winline -Wstrict-prototypes -Wnested-externs -Wpointer-arith -Wcast-align
WARN_FLAGS_MAX     = $(WARN_FLAGS) -Wcast-qual -Wshadow
CPP_WARN_FLAGS     = -Wall -W -Wwrite-strings -Winline -Wpointer-arith -Wcast-align
CPP_WARN_FLAGS_MAX = $(CPP_WARN_FLAGS) -Wcast-qual -Wshadow

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: GNU C Compiler
CC = gcc

# Linker: GNU Linker
LD = g++

# C++ Compiler: GNU C++ Compiler
CPP = g++

# C++ Linker: GNU C++ Linker
CPP_LD = g++

# Archiver: GNU Archiver
AR = ar

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%/bin/glnxa64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  = @rm -f
ECHO                = @echo
MV                  = @mv
RUN                 =

#----------------------------------------
# "Faster Builds" Build Configuration
#----------------------------------------

ARFLAGS              = ruvs
CFLAGS               = -c $(C_STANDARD_OPTS) -fPIC \
                       -O0
CPPFLAGS             = -c $(CPP_STANDARD_OPTS) -fPIC \
                       -O0
CPP_LDFLAGS          =
CPP_SHAREDLIB_LDFLAGS  = -shared -Wl,--no-undefined
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              =
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -shared -Wl,--no-undefined



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)/dp
PRODUCT_TYPE = "executable"
BUILD_TYPE = "Top-Level Standalone Executable"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR) -I$(START_DIR)/dp_grt_rtw -I$(MATLAB_ROOT)/extern/include -I$(MATLAB_ROOT)/simulink/include -I$(MATLAB_ROOT)/rtw/c/src -I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common -I$(MATLAB_ROOT)/extern/physmod/glnxa64/lang/include -I$(MATLAB_ROOT)/extern/physmod/glnxa64/mc/include -I$(MATLAB_ROOT)/extern/physmod/glnxa64/pd/include -I$(MATLAB_ROOT)/extern/physmod/glnxa64/pm/include -I$(MATLAB_ROOT)/extern/physmod/glnxa64/pm_log/include -I$(MATLAB_ROOT)/extern/physmod/glnxa64/pm_math/include -I$(MATLAB_ROOT)/extern/physmod/glnxa64/sm/include -I$(MATLAB_ROOT)/extern/physmod/glnxa64/sm_ssci/include -I$(MATLAB_ROOT)/extern/physmod/glnxa64/ssc_comp/include -I$(MATLAB_ROOT)/extern/physmod/glnxa64/ssc_core/include -I$(MATLAB_ROOT)/extern/physmod/glnxa64/ssc_ds/include -I$(MATLAB_ROOT)/extern/physmod/glnxa64/ssc_sli/include -I$(MATLAB_ROOT)/extern/physmod/glnxa64/ssc_st/include

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_BUILD_ARGS = -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0 -DMAT_FILE=1 -DONESTEPFCN=1 -DTERMFCN=1 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=0
DEFINES_CUSTOM = 
DEFINES_OPTS = -DTID01EQ=1
DEFINES_STANDARD = -DMODEL=dp -DNUMST=2 -DNCSTATES=4 -DHAVESTDIO -DRT -DUSE_RTMODEL

DEFINES = $(DEFINES_BUILD_ARGS) $(DEFINES_CUSTOM) $(DEFINES_OPTS) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1.c $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_create.c $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_setParameters.c $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_asserts.c $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_deriv.c $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_checkDynamics.c $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_compOutputs.c $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_asm_delegate.c $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_sim_delegate.c $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_mode_zero_crossings.c $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_logging.c $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_geometries.c $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_gateway.c $(MATLAB_ROOT)/rtw/c/src/rt_logging.c $(START_DIR)/dp_grt_rtw/rt_backsubrr_dbl.c $(START_DIR)/dp_grt_rtw/rt_forwardsubrr_dbl.c $(START_DIR)/dp_grt_rtw/rt_lu_real.c $(START_DIR)/dp_grt_rtw/rt_matrixlib_dbl.c $(START_DIR)/dp_grt_rtw/dp.c $(START_DIR)/dp_grt_rtw/rtGetInf.c $(START_DIR)/dp_grt_rtw/rtGetNaN.c $(START_DIR)/dp_grt_rtw/rt_nonfinite.c

MAIN_SRC = $(MATLAB_ROOT)/rtw/c/src/common/rt_main.c

ALL_SRCS = $(SRCS) $(MAIN_SRC)

###########################################################################
## OBJECTS
###########################################################################

OBJS = dp_a151ee3d_1.o dp_a151ee3d_1_create.o dp_a151ee3d_1_setParameters.o dp_a151ee3d_1_asserts.o dp_a151ee3d_1_deriv.o dp_a151ee3d_1_checkDynamics.o dp_a151ee3d_1_compOutputs.o dp_a151ee3d_1_asm_delegate.o dp_a151ee3d_1_sim_delegate.o dp_a151ee3d_1_mode_zero_crossings.o dp_a151ee3d_1_logging.o dp_a151ee3d_1_geometries.o dp_a151ee3d_1_gateway.o rt_logging.o rt_backsubrr_dbl.o rt_forwardsubrr_dbl.o rt_lu_real.o rt_matrixlib_dbl.o dp.o rtGetInf.o rtGetNaN.o rt_nonfinite.o

MAIN_OBJ = rt_main.o

ALL_OBJS = $(OBJS) $(MAIN_OBJ)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = $(MATLAB_ROOT)/extern/physmod/glnxa64/ssc_sli/lib/ssc_sli_std.a $(MATLAB_ROOT)/extern/physmod/glnxa64/sm_ssci/lib/sm_ssci_std.a $(MATLAB_ROOT)/extern/physmod/glnxa64/ssc_core/lib/ssc_core_std.a $(MATLAB_ROOT)/extern/physmod/glnxa64/ssc_st/lib/ssc_st_std.a $(MATLAB_ROOT)/extern/physmod/glnxa64/mc/lib/mc_std.a $(MATLAB_ROOT)/extern/physmod/glnxa64/sm/lib/sm_std.a $(MATLAB_ROOT)/extern/physmod/glnxa64/pm_math/lib/pm_math_std.a $(MATLAB_ROOT)/extern/physmod/glnxa64/pm/lib/pm_std.a

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_TFL = -msse2
CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_TFL) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_TFL = -msse2
CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_TFL) $(CPPFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build buildobj clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


buildobj : prebuild $(OBJS) $(PREBUILT_OBJS) $(LIBS)
	@echo "### Successfully generated all binary outputs."


prebuild : 


download : $(PRODUCT)


execute : download
	@echo "### Invoking postbuild tool "Execute" ..."
	$(EXECUTE) $(EXECUTE_FLAGS)
	@echo "### Done invoking postbuild tool."


###########################################################################
## FINAL TARGET
###########################################################################

#-------------------------------------------
# Create a standalone executable            
#-------------------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS) $(LIBS) $(MAIN_OBJ)
	@echo "### Creating standalone executable "$(PRODUCT)" ..."
	$(LD) $(LDFLAGS) -o $(PRODUCT) $(OBJS) $(MAIN_OBJ) -Wl,--start-group $(LIBS) -Wl,--end-group $(SYSTEM_LIBS) $(TOOLCHAIN_LIBS)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.o : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/extern/physmod/glnxa64/mc/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/extern/physmod/glnxa64/mc/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/extern/physmod/glnxa64/pm/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/extern/physmod/glnxa64/pm/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/extern/physmod/glnxa64/pm_math/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/extern/physmod/glnxa64/pm_math/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/extern/physmod/glnxa64/sm/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/extern/physmod/glnxa64/sm/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/extern/physmod/glnxa64/sm_ssci/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/extern/physmod/glnxa64/sm_ssci/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/extern/physmod/glnxa64/ssc_core/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/extern/physmod/glnxa64/ssc_core/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/extern/physmod/glnxa64/ssc_sli/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/extern/physmod/glnxa64/ssc_sli/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/extern/physmod/glnxa64/ssc_st/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/extern/physmod/glnxa64/ssc_st/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/dp_grt_rtw/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/dp_grt_rtw/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/simulink/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/simulink/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


dp_a151ee3d_1.o : $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1.c
	$(CC) $(CFLAGS) -o "$@" "$<"


dp_a151ee3d_1_create.o : $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_create.c
	$(CC) $(CFLAGS) -o "$@" "$<"


dp_a151ee3d_1_setParameters.o : $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_setParameters.c
	$(CC) $(CFLAGS) -o "$@" "$<"


dp_a151ee3d_1_asserts.o : $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_asserts.c
	$(CC) $(CFLAGS) -o "$@" "$<"


dp_a151ee3d_1_deriv.o : $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_deriv.c
	$(CC) $(CFLAGS) -o "$@" "$<"


dp_a151ee3d_1_checkDynamics.o : $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_checkDynamics.c
	$(CC) $(CFLAGS) -o "$@" "$<"


dp_a151ee3d_1_compOutputs.o : $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_compOutputs.c
	$(CC) $(CFLAGS) -o "$@" "$<"


dp_a151ee3d_1_asm_delegate.o : $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_asm_delegate.c
	$(CC) $(CFLAGS) -o "$@" "$<"


dp_a151ee3d_1_sim_delegate.o : $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_sim_delegate.c
	$(CC) $(CFLAGS) -o "$@" "$<"


dp_a151ee3d_1_mode_zero_crossings.o : $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_mode_zero_crossings.c
	$(CC) $(CFLAGS) -o "$@" "$<"


dp_a151ee3d_1_logging.o : $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_logging.c
	$(CC) $(CFLAGS) -o "$@" "$<"


dp_a151ee3d_1_geometries.o : $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_geometries.c
	$(CC) $(CFLAGS) -o "$@" "$<"


dp_a151ee3d_1_gateway.o : $(START_DIR)/dp_grt_rtw/dp_a151ee3d_1_gateway.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rt_logging.o : $(MATLAB_ROOT)/rtw/c/src/rt_logging.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rt_backsubrr_dbl.o : $(START_DIR)/dp_grt_rtw/rt_backsubrr_dbl.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rt_forwardsubrr_dbl.o : $(START_DIR)/dp_grt_rtw/rt_forwardsubrr_dbl.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rt_lu_real.o : $(START_DIR)/dp_grt_rtw/rt_lu_real.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rt_matrixlib_dbl.o : $(START_DIR)/dp_grt_rtw/rt_matrixlib_dbl.c
	$(CC) $(CFLAGS) -o "$@" "$<"


dp.o : $(START_DIR)/dp_grt_rtw/dp.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetInf.o : $(START_DIR)/dp_grt_rtw/rtGetInf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetNaN.o : $(START_DIR)/dp_grt_rtw/rtGetNaN.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rt_nonfinite.o : $(START_DIR)/dp_grt_rtw/rt_nonfinite.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rt_main.o : $(MATLAB_ROOT)/rtw/c/src/common/rt_main.c
	$(CC) $(CFLAGS) -o "$@" "$<"


#------------------------
# BUILDABLE LIBRARIES
#------------------------

$(MATLAB_ROOT)/extern/physmod/glnxa64/ssc_sli/lib/ssc_sli_std.a : $(LIBSSC_SLI_STD_OBJS)
	@echo "### Creating static library $@ ..."
	$(AR) $(ARFLAGS)  $@ $(LIBSSC_SLI_STD_OBJS)


$(MATLAB_ROOT)/extern/physmod/glnxa64/sm_ssci/lib/sm_ssci_std.a : $(LIBSM_SSCI_STD_OBJS)
	@echo "### Creating static library $@ ..."
	$(AR) $(ARFLAGS)  $@ $(LIBSM_SSCI_STD_OBJS)


$(MATLAB_ROOT)/extern/physmod/glnxa64/ssc_core/lib/ssc_core_std.a : $(LIBSSC_CORE_STD_OBJS)
	@echo "### Creating static library $@ ..."
	$(AR) $(ARFLAGS)  $@ $(LIBSSC_CORE_STD_OBJS)


$(MATLAB_ROOT)/extern/physmod/glnxa64/ssc_st/lib/ssc_st_std.a : $(LIBSSC_ST_STD_OBJS)
	@echo "### Creating static library $@ ..."
	$(AR) $(ARFLAGS)  $@ $(LIBSSC_ST_STD_OBJS)


$(MATLAB_ROOT)/extern/physmod/glnxa64/mc/lib/mc_std.a : $(LIBMC_STD_OBJS)
	@echo "### Creating static library $@ ..."
	$(AR) $(ARFLAGS)  $@ $(LIBMC_STD_OBJS)


$(MATLAB_ROOT)/extern/physmod/glnxa64/sm/lib/sm_std.a : $(LIBSM_STD_OBJS)
	@echo "### Creating static library $@ ..."
	$(AR) $(ARFLAGS)  $@ $(LIBSM_STD_OBJS)


$(MATLAB_ROOT)/extern/physmod/glnxa64/pm_math/lib/pm_math_std.a : $(LIBPM_MATH_STD_OBJS)
	@echo "### Creating static library $@ ..."
	$(AR) $(ARFLAGS)  $@ $(LIBPM_MATH_STD_OBJS)


$(MATLAB_ROOT)/extern/physmod/glnxa64/pm/lib/pm_std.a : $(LIBPM_STD_OBJS)
	@echo "### Creating static library $@ ..."
	$(AR) $(ARFLAGS)  $@ $(LIBPM_STD_OBJS)


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### CPPFLAGS = $(CPPFLAGS)"
	@echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."


