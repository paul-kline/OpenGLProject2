CPP = g++
INC = -I../cryphutil -I../fontutil -I../glslutil -I../mvcutil
C_FLAGS = -fPIC -g -c -DGL_GLEXT_PROTOTYPES $(INC)

LINK = g++ -fPIC -g
LOCAL_UTIL_LIBRARIES = -L../lib -lcryph -lfont -lglsl -lmvc
OGL_LIBRARIES = -lglfw -lGLU -lGL

OBJS = project2.o Simpleshape.o getMatrices.o Cylinder.o Column.o
all:
	$(MAKE) -C ../mvcutil
	$(MAKE) project2

project2: $(OBJS) ../lib/libcryph.so ../lib/libfont.so ../lib/libglsl.so ../lib/libmvc.so
	$(LINK) -o project2 $(OBJS) $(LOCAL_UTIL_LIBRARIES) $(OGL_LIBRARIES)

../lib/libcryph.so: ../cryphutil/AffVector.h ../cryphutil/AffVector.c++ ../cryphutil/AffPoint.h ../cryphutil/AffPoint.c++
	(cd ../cryphutil; make)

../lib/libfont.so: ../fontutil/CFont.h ../fontutil/CFont.c++ ../fontutil/CGLString.h ../fontutil/CGLString.c++
	(cd ../fontutil; make)

../lib/libglsl.so: ../glslutil/ShaderIF.h ../glslutil/ShaderIF.c++
	(cd ../glslutil; make)

../lib/libmvc.so: ../mvcutil/Controller.h ../mvcutil/Controller.c++ ../mvcutil/ModelView.h ../mvcutil/ModelView.c++
	(cd ../mvcutil; make)

project2.o: project2.c++
	$(CPP) $(C_FLAGS) project2.c++
getMatrices.o: getMatrices.c++
	$(CPP) $(C_FLAGS) getMatrices.c++
Column.o: Column.h Column.c++
	$(CPP) $(C_FLAGS) Column.c++
Simpleshape.o: Simpleshape.h Simpleshape.c++
	$(CPP) $(C_FLAGS) Simpleshape.c++
Cylinder.o: Cylinder.h Cylinder.c++
	$(CPP) $(C_FLAGS) Cylinder.c++
	
	
clean:
	rm -f ../mvcutil/ModelView.o ../mvcutil/ModelViewWithLighting.o ./*.o