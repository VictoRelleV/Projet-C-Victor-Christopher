mkdir -p build;
cd build;
cmake ..;
make OlympicBasketball;
cp ./OlympicBasketball ../;
cd ..;
./OlympicBasketball;
rm ./OlympicBasketball;