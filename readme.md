## Install OpenCV 4.9 with CUDA support
!! You have to have cuda installation with cublas and cudnn. Tested with 11.8 cuda, 8.6.0.163 cudnn

Cmake and GCC 
```
sudo apt install cmake
sudo apt install gcc g++
```

Python3 deps
```
sudo apt install python3 python3-dev python3-numpy
```

GTK is requried for GUI features, Camera support (v4l), Media Support (ffmpeg, gstreamer…), etc.:

```
sudo apt install libavcodec-dev libavformat-dev libswscale-dev
sudo apt install libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev 
sudo apt install libgtk-3-dev
```

The next dependencies are optional but add the latest support for PNG, JPEG, JPEG2000, TIFF, WebP, etc. formats:

```
sudo apt install libpng-dev libjpeg-dev libopenexr-dev libtiff-dev libwebp-dev
```

Clone the 4.9.0 tag branch from OpenCV repository
```
git clone https://github.com/opencv/opencv.git --branch 4.9.0 --single-branch --depth 1
```

Clone the 4.9.0 tag branch from OpenCV-contrib repository for extra modules
```
git clone https://github.com/opencv/opencv_contrib.git --branch 4.9.0 --single-branch --depth 1
```

Go to this [page](https://developer.nvidia.com/cuda-gpus) and find your gpus compute capability to set "$CUDA_ARCH_BIN" flag during the cmake build. For RTX 4060ti it is 8.9:

### Build
Refer [here](https://docs.opencv.org/4.x/db/d05/tutorial_config_reference.html) for build flags

```
cd ~/opencv && mkdir build && cd build
```
Run cmake configurations
```
cmake \
-D CMAKE_BUILD_TYPE=RELEASE \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D WITH_CUDA=ON \
-D WITH_CUDNN=ON \
-D WITH_CUBLAS=ON \
-D WITH_TBB=ON \
-D OPENCV_DNN_CUDA=ON \
-D OPENCV_ENABLE_NONFREE=ON \
-D CUDA_ARCH_BIN=6.1 \
-D OPENCV_EXTRA_MODULES_PATH=$HOME/projects/opencv_contrib/modules \
-D BUILD_EXAMPLES=OFF \
-D HAVE_opencv_python3=ON \
-D BUILD_SHARED_LIBS=ON \
..
```
(Optional) It might give warnings for NVCODEC -> Nvidia Video Codec SDK. It means you dont have the packages. If you have just put them into LD_LIBRARY_PATH.

Give the # of threads you have on your CPU to increase the build speed. e.g 16
```
make -j16
```

Install the built packages
```
sudo make install
```

Link and refresh the loader and linker
```
sudo ldconfig
```

Done ! You can remove both of the repositories on your system.