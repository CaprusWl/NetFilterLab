cd kernel &&
sudo rmmod NetFireWallModule.ko;
make clean &&
make &&
sudo insmod NetFireWallModule.ko;
cd ..
