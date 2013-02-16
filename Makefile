buildDir=build

$(shell mkdir -p $(buildDir))

#acceptable buildTypes: Release/Debug/Profile
buildType=Release

.SILENT: 

all: compile_all

cmake: CMakeLists.txt
	cd $(buildDir) && cmake -DCMAKE_BUILD_TYPE=$(buildType) ..

compile_all: cmake 
	$(MAKE) --no-print-directory -C $(buildDir)

clean:
	$(MAKE) --no-print-directory -C $(buildDir) clean
	
cleanup_cache:
	cd $(buildDir) && rm -rf *

