# Homography Transformer (Video)

## Parameters

- H: Homography matrix 3*3 (if you have the matrix stored in txt file, you can read it using the function HomographyTransformer::readMatrix)
- new_plane_width, new_plane_height: the new image dimensions
- multiplication_ratio: how much do you want to scale the output image (its value depend on your correspondences which you used to calculate the homography matrix), if the value is 1 then no scaling will be applied
- starting_x, starting_y: how many pixels do you want to translate the output image

## Build the app

```shell
mkdir build #if build directory is not exist
cd build
cmake ..
make
```

## Run examples

```shell
./build/my_app files/homography.txt files/input.mkv files/output_wide.mkv 1000 700 40 -450 -130
```

```shell
./build/my_app files/homography.txt files/input.mkv files/output_narrow.mkv 450 1000 100 -100 425
```

```shell
./build/my_app files/homography.txt files/input.mkv files/output_narrow2.mkv 650 1000 100 -200 425
```
