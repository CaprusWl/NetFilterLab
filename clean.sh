cd kernel &&
sudo rmmod NetFireWallModule.ko;
make clean;
cd ../client &&
make clean
