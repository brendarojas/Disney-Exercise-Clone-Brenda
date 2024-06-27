# Disney Support Engineer + QA / Take-Home Exercise

This is the repository for the Disney Support Engineer + QA / Take-Home Exercise

## Content

* [Description](#Desc)
* [Prerequisites](#Prer)
* [Compiling](#Comp)
 
<a name="Desc"></a>

## Description

This Repository contains the implementation of a (mock) Menu for a Streaming service, in C++ language.

<a name="Prer"></a>

## Prerequisites

* Libraries

    You will need to install curl library to be able to compile correctly.
     in debian/ubuntu, just execute:

  ```
  sudo apt install libcurl4-openssl-dev
  ```

    For graphics rendering, the SDL2 library is also required

  ```
  sudo apt install libsdl2-dev
  ```

    For dealing with images, we will need SDL Image Library.

  ```
  sudo apt install libsdl2-image-dev
  ```

    For dealing with fonts, we weel need SDL Font Library.
    
  ```
  sudo apt install libsdl2-font-dev
  ```    

If any of these libraries are not found, it may have changed its name. Try to find an alterantive that contains the same header files.

<a name="Comp"></a>

## Building (Compiling) the program

For compiling, after downloading the source code, just go to the directory and execute:

```
make
```

The compiled executable will be in the `output` directory.

<a name="Exec"></a>

## Executing the program

To run the program, just execute:

```
./output/DSS
```

A window will pop up, and the splash disney logo should appear.

After the data is fetched from the URLs, the images will appear on screen.

User is able to navigate through the items. The currently selected item is highlighted with a gray border.

With the arrows of the keyboard, user is able to change currently selected item.
