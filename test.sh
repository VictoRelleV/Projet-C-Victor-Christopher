mkdir -p build;
cd build;
cmake ..;
make OlympicBasketball_test;
cp ./OlympicBasketball_test ../;
cd ..;
./OlympicBasketball_test;
rm ./OlympicBasketball_test;