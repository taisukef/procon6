# Microsoft Visual C++ generated build script - Do not modify

PROJ = VPC
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\WORK\VPC\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = /YcSTDAFX.H
CUSEPCHFLAG = 
CPPUSEPCHFLAG = /YuSTDAFX.H
FIRSTC =             
FIRSTCPP = STDAFX.CPP  
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AM /Od /D "_DEBUG" /FR /GA /Fd"VPC.PDB" 
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AM /O2 /Ob2 /D "NDEBUG" /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE
LIBS_D_WEXE = mafxcwd oldnames libw mlibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = mafxcw oldnames libw mlibcew commdlg.lib shell.lib 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = VPC.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = STDAFX.SBR \
		VPC.SBR \
		MAINFRM.SBR \
		VPCDOC.SBR \
		VPCVIEW.SBR \
		DIB.SBR \
		RGB.SBR \
		VPCDLG.SBR \
		LRGB.SBR \
		CONFNCS.SBR


VPC_RCDEP = d:\work\vpc\res\vpc.ico \
	d:\work\vpc\res\cur_noma.cur \
	d:\work\vpc\res\vpc.rc2


STDAFX_DEP = d:\work\vpc\stdafx.h


VPC_DEP = d:\work\vpc\stdafx.h \
	d:\work\vpc\vpc.h \
	d:\work\vpc\mainfrm.h \
	d:\work\vpc\vpcdoc.h \
	d:\work\vpc\vpcview.h \
	d:\work\vpc\dib.h \
	d:\work\vpc\rgb.h \
	d:\work\vpc\lrgb.h


MAINFRM_DEP = d:\work\vpc\stdafx.h \
	d:\work\vpc\vpc.h \
	d:\work\vpc\mainfrm.h


VPCDOC_DEP = d:\work\vpc\stdafx.h \
	d:\work\vpc\vpc.h \
	d:\work\vpc\vpcdoc.h


VPCVIEW_DEP = d:\work\vpc\stdafx.h \
	d:\work\vpc\vpc.h \
	d:\work\vpc\vpcdoc.h \
	d:\work\vpc\vpcview.h \
	d:\work\vpc\dib.h \
	d:\work\vpc\rgb.h \
	d:\work\vpc\lrgb.h \
	d:\work\vpc\vpcdlg.h


DIB_DEP = d:\work\vpc\stdafx.h \
	d:\work\vpc\dib.h


RGB_DEP = d:\work\vpc\stdafx.h \
	d:\work\vpc\rgb.h


VPCDLG_DEP = d:\work\vpc\stdafx.h \
	d:\work\vpc\vpc.h \
	d:\work\vpc\vpcdlg.h


LRGB_DEP = d:\work\vpc\stdafx.h \
	d:\work\vpc\lrgb.h


CONFNCS_DEP = d:\work\vpc\stdafx.h \
	d:\work\vpc\vpc.h \
	d:\work\vpc\vpcdoc.h \
	d:\work\vpc\vpcview.h \
	d:\work\vpc\dib.h \
	d:\work\vpc\rgb.h \
	d:\work\vpc\lrgb.h


all:	$(PROJ).EXE

VPC.RES:	VPC.RC $(VPC_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r VPC.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

VPC.OBJ:	VPC.CPP $(VPC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c VPC.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

VPCDOC.OBJ:	VPCDOC.CPP $(VPCDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c VPCDOC.CPP

VPCVIEW.OBJ:	VPCVIEW.CPP $(VPCVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c VPCVIEW.CPP

DIB.OBJ:	DIB.CPP $(DIB_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DIB.CPP

RGB.OBJ:	RGB.CPP $(RGB_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RGB.CPP

VPCDLG.OBJ:	VPCDLG.CPP $(VPCDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c VPCDLG.CPP

LRGB.OBJ:	LRGB.CPP $(LRGB_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c LRGB.CPP

CONFNCS.OBJ:	CONFNCS.CPP $(CONFNCS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CONFNCS.CPP


$(PROJ).EXE::	VPC.RES

$(PROJ).EXE::	STDAFX.OBJ VPC.OBJ MAINFRM.OBJ VPCDOC.OBJ VPCVIEW.OBJ DIB.OBJ RGB.OBJ \
	VPCDLG.OBJ LRGB.OBJ CONFNCS.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
VPC.OBJ +
MAINFRM.OBJ +
VPCDOC.OBJ +
VPCVIEW.OBJ +
DIB.OBJ +
RGB.OBJ +
VPCDLG.OBJ +
LRGB.OBJ +
CONFNCS.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
d:\msvc\lib\+
d:\msvc\mfc\lib\+
d:\msvc\wing\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) VPC.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	VPC.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) VPC.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
