#!/bin/bash

rm -rf bin test.jar &&\
    mkdir bin &&\
    javac -cp ./bin/ -d ./bin/ src/CubePackage/Cube.java &&\
    javac -cp ./bin/ -d ./bin/ src/CubePackage/CubeSheet.java &&\
    javac -cp ./bin/ -d ./bin/ src/CubePackage/Work.java &&\
    javac -cp ./bin/ -d ./bin/ src/CubePackage/Window.java &&\
    javac -cp ./bin/ -d ./bin/ src/MainPackage/MainClass.java &&\
    echo "Main-Class: MainPackage/MainClass" > bin/manifest.mf &&\
    cd bin &&\
    jar -cvfm test.jar manifest.mf CubePackage/ MainPackage/ &&\
    cd ../ &&\
    ln -s bin/test.jar &&\
    java -jar test.jar


