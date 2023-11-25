CXX = g++ --std=c++11
CFLAGS = -Wall
BUILD_NAME = ./Exe/test
OBJ_PATH = .
INC_PATH = -I .././includes -I .././includes/freetypeinc -I .././includes/freetypeinc/freetype
LINKER_MAC = -L. .././lib/mac/libglfw.3.3.dylib -L. .././lib/mac/libfreetype.6.dylib
LINKER_WIN = -L. .././lib/win/libglfw3dll.a -L. .././lib/win/libfreetype.dll.a
DIR_OFF = ../platforms/OpenGL_Base/
SRC_OFF = ../Sandbox/
MVIZ_SRC_OFF = ../MViz/
ABS_OFF = ../Core/

UNAME_S := $(shell uname -s)
ASSEMBLE_CMD = 	${CXX} ${CFLAGS} -c

FILE_DEPENDENCIES = glad.obj Shader.obj Window.obj Application.obj BufferObject.obj Graph.obj Text.obj Input.obj UI.obj

MAC_COMMAND = ${CXX} ${CFLAGS} -o ${BUILD_NAME} ${OBJ_PATH}/*.obj ${INC_PATH} ${LINKER_MAC}
WIN_COMMAND = ${CXX} ${CFLAGS} -o ${BUILD_NAME} ${OBJ_PATH}/*.obj ${INC_PATH} ${LINKER_WIN}

mviz: main.obj ${FILE_DEPENDENCIES}
ifeq (${UNAME_S}, Darwin)
	${MAC_COMMAND}
else
	$(WIN_COMMAND)
endif

mviz_clean:	clean mviz

sanbox: sandbox.obj ${FILE_DEPENDENCIES}
ifeq (${UNAME_S}, Darwin)
	${MAC_COMMAND}
else
	$(WIN_COMMAND)
endif

sandbox_clean: clean build_m

main.obj: ${MVIZ_SRC_OFF}Application.cpp ${MVIZ_SRC_OFF}MVizUI.cpp 
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/main.obj ${INC_PATH} ${MVIZ_SRC_OFF}Application.cpp

sandbox.obj: ${SRC_OFF}main.cpp ${SRC_OFF}Application.hpp 
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/main.obj ${INC_PATH} ${SRC_OFF}main.cpp

glad.obj: ${SRC_OFF}glad.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/glad.obj ${SRC_OFF}glad.cpp

Shader.obj: ${DIR_OFF}OpenGL_Sha.cpp 
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/Shader.obj ${DIR_OFF}OpenGL_Sha.cpp

Window.obj: ${DIR_OFF}OpenGL_Win.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/Window.obj ${INC_PATH} ${DIR_OFF}OpenGL_Win.cpp

Application.obj: ${DIR_OFF}OpenGL_App.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/Application.obj ${INC_PATH} ${DIR_OFF}OpenGL_App.cpp

BufferObject.obj: ${DIR_OFF}OpenGL_Buff.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/BufferObject.obj ${DIR_OFF}OpenGL_Buff.cpp

Graph.obj: ${DIR_OFF}OpenGL_Graph.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/Graph.obj ${INC_PATH} ${DIR_OFF}OpenGL_Graph.cpp

Text.obj: ${DIR_OFF}OpenGL_Text.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/Text.obj ${INC_PATH} ${DIR_OFF}OpenGL_Text.cpp

Input.obj: ${DIR_OFF}OpenGL_Inp.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/Input.obj ${DIR_OFF}OpenGL_Inp.cpp

UI.obj: ${DIR_OFF}OpenGL_UI.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/UI.obj ${INC_PATH} ${DIR_OFF}OpenGL_UI.cpp

clean:
ifeq (${UNAME_S}, Darwin)
	rm -f *.obj
else
	del -f *.obj
endif