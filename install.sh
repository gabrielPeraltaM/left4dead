#! /bin/bash
echo "Installing dependencies..."
sudo apt-get install libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev libsdl2-dev

echo "Installing SDL2..."
git clone https://github.com/libsdl-org/SDL.git
cd SDL || exit
mkdir build
cd build
cmake ..
make
sudo make install
cd ../..

echo "Installing SDL2_mixer..."
git clone https://github.com/libsdl-org/SDL_mixer.git
cd SDL_mixer || exit
mkdir build
cd build
cmake ..
make
sudo make install
cd ../..

echo "Installing SDL2_image..."
git clone https://github.com/libsdl-org/SDL_image.git
cd SDL_image || exit
mkdir build
cd build
cmake ..
make
sudo make install
cd ../..

echo "Installing QT5..."
sudo apt-get install qt5-default qttools5-dev-tools qt5-doc qt5-doc-html qtbase5-doc-html build-essential libgl1-mesa-dev

echo "Deleting temporary files..."
rm -rf SDL SDL_mixer SDL_image

echo "Building..."
mkdir build
cd build || exit
cmake ..
make

echo "Done!"

echo "To start the server, run ./server <some port> in the build directory."
echo "To start the client, run ./client <server ip> <server port> in the build directory."
