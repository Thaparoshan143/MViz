CXX = g++ --std=c++11
CFLAGS = -Wall
BUILD_NAME = ./Exe/test
OBJ_PATH = .
INC_PATH = -I .././includes -I .././includes/freetypeinc -I .././includes/freetypeinc/freetype
LINKER_MAC = -L. .././lib/mac/libglfw.3.3.dylib -L. .././lib/mac/libfreetype.6.dylib
LINKER_WIN = -L. .././lib/win/libglfw3dll.a -L. .././lib/win/libfreetype.dll.a
PLATFORM_DIR_OFF = ../platforms/OpenGL_Base/
MVIZ_SRC_OFF = ../MViz/

UNAME_S := $(shell uname -s)
ASSEMBLE_CMD = 	${CXX} ${CFLAGS} -c

FILE_DEPENDENCIES = glad.obj Shader.obj Window.obj Application.obj BufferObject.obj Graph.obj Text.obj UI.obj

MAC_COMMAND = ${CXX} ${CFLAGS} -o ${BUILD_NAME} ${OBJ_PATH}/*.obj ${INC_PATH} ${LINKER_MAC}
WIN_COMMAND = ${CXX} ${CFLAGS} -o ${BUILD_NAME} ${OBJ_PATH}/*.obj ${INC_PATH} ${LINKER_WIN}

mviz: ${FILE_DEPENDENCIES} main.obj 
ifeq (${UNAME_S}, Darwin)
	${MAC_COMMAND}
else
	$(WIN_COMMAND)
endif

mviz_clean:	clean mviz

main.obj: ${MVIZ_SRC_OFF}Application.cpp ${MVIZ_SRC_OFF}MVizUI.cpp ${MVIZ_SRC_OFF}MVizGraph.cpp 
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/main.obj ${INC_PATH} ${MVIZ_SRC_OFF}Application.cpp

glad.obj: ${MVIZ_SRC_OFF}glad.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/glad.obj ${MVIZ_SRC_OFF}glad.cpp

Shader.obj: ${PLATFORM_DIR_OFF}OpenGL_Sha.cpp 
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/Shader.obj ${PLATFORM_DIR_OFF}OpenGL_Sha.cpp

Window.obj: ${PLATFORM_DIR_OFF}OpenGL_Win.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/Window.obj ${INC_PATH} ${PLATFORM_DIR_OFF}OpenGL_Win.cpp

Application.obj: ${PLATFORM_DIR_OFF}OpenGL_App.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/Application.obj ${INC_PATH} ${PLATFORM_DIR_OFF}OpenGL_App.cpp

BufferObject.obj: ${PLATFORM_DIR_OFF}OpenGL_Buff.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/BufferObject.obj ${PLATFORM_DIR_OFF}OpenGL_Buff.cpp

Graph.obj: ${PLATFORM_DIR_OFF}OpenGL_Graph.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/Graph.obj ${INC_PATH} ${PLATFORM_DIR_OFF}OpenGL_Graph.cpp

Text.obj: ${PLATFORM_DIR_OFF}OpenGL_Text.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/Text.obj ${INC_PATH} ${PLATFORM_DIR_OFF}OpenGL_Text.cpp

UI.obj: ${PLATFORM_DIR_OFF}OpenGL_UI.cpp
	${ASSEMBLE_CMD} -o ${OBJ_PATH}/UI.obj ${INC_PATH} ${PLATFORM_DIR_OFF}OpenGL_UI.cpp

clean:
ifeq (${UNAME_S}, Darwin)
	rm -f *.obj
else
	del -f *.obj
endif