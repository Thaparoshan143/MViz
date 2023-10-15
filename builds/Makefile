CXX = g++ --std=c++11
CFLAGS = -Wall
BUILD_NAME = ./Exe/test
OBJ_PATH = .
INC_PATH = -I./includes
LINKER_MAC = -L. .././lib/mac/libglfw.3.3.dylib
LINKER_WIN = -L. .././lib/win/libglfw3dll.a
DIR_OFF = ../platforms/OpenGL_Base/
SRC_OFF = ../Sandbox/
ABS_OFF = ../Core/

ASSEMBLE_CMD = 	${CXX} ${CFLAGS} -c

FILE_DEPENDENCIES = main.obj glad.obj Shader.obj Window.obj Application.obj VertexBuffer.obj

MAC_COMMAND = ${CXX} ${CFLAGS} -o ${BUILD_NAME} ${OBJ_PATH}/*.obj ${INC_PATH} ${LINKER_MAC}

WIN_COMMAND = ${CXX} ${CFLAGS} -o ${BUILD_NAME} ${OBJ_PATH}/*.obj ${INC_PATH} ${LINKER_WIN}

mac_m: ${FILE_DEPENDENCIES}
	${MAC_COMMAND}

win_m: ${FILE_DEPENDENCIES}
	$(WIN_COMMAND)

main.obj: ${SRC_OFF}main.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/main.obj ${SRC_OFF}main.cpp

glad.obj: ${SRC_OFF}glad.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/glad.obj ${SRC_OFF}glad.cpp

Shader.obj: ${DIR_OFF}OpenGL_Sha.cpp 
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/Shader.obj ${DIR_OFF}OpenGL_Sha.cpp

Window.obj: ${DIR_OFF}OpenGL_Win.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/Window.obj ${DIR_OFF}OpenGL_Win.cpp

Application.obj: ${DIR_OFF}OpenGL_App.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/Application.obj ${DIR_OFF}OpenGL_App.cpp

VertexBuffer.obj: ${DIR_OFF}OpenGL_VertBuff.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/VertexBuffer.obj ${DIR_OFF}OpenGL_VertBuff.cpp


clean_win:
	del -f *.obj

clean_mac:
	rm -f *.obj
	