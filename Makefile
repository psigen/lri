# Build variables
BUILD_DIR=build
CMAKE=cmake

# Build directory
$(shell mkdir -p $(BUILD_DIR))

#acceptable BUILD_TYPE: Release/Debug/Profile
BUILD_TYPE=Release

.SILENT: 

all: compile_all

cmake: CMakeLists.txt
	cd $(BUILD_DIR) && $(CMAKE) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) ..

compile_all: cmake 
	$(MAKE) --no-print-directory -C $(BUILD_DIR)

clean:
	$(MAKE) --no-print-directory -C $(BUILD_DIR) clean

cleanup_cache:
	cd $(BUILD_DIR) && rm -rf *

