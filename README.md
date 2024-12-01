# BBT Monochrome Image Creator

This program allows you to create `.bbt` monochrome images where the pixels are either black (`1`) or white (`0`). The program uses a custom binary format (`.bbt`) to store the image, which can be later read and displayed. The user inputs the image as a canvas of `1` (black) and `0` (white), which are then converted into pixel data.

## Features
- Create a `.bbt` image with black and white pixels.
- Input the canvas as a series of lines containing `1` and `0` to represent black and white pixels, respectively.
- The program saves the generated image in the `.bbt` format, which can be later read by the `bbt_reader` program (or any other custom reader).
- Custom image dimensions are based on user input.

## File Format

The `.bbt` file format consists of two main components:
1. **Header**:
    - `signature`: A constant value `0x42425400` to identify the file format.
    - `width`: The width of the image in pixels.
    - `height`: The height of the image in pixels.
    - `depth`: The color depth, which is always 24 for this format (RGB).

2. **Pixel Data**: Each pixel is represented by 3 bytes (one for each RGB channel). Black pixels (`1`) are represented as `RGB(0, 0, 0)` and white pixels (`0`) are represented as `RGB(255, 255, 255)`.

## Compilation and Usage

### Requirements
- A C compiler (e.g., GCC).
- A `DynamicStringArray` implementation to manage the canvas input.

### Compilation
To compile the program, use the following command:

```bash
gcc -o monochrome monochrome.c bbtSrc.c DynamicStringArray.c -lm
```

### Running the Program
To run the program, use the following command:

```bash
./bbt_monochrome_creator
```

### Program Flow
1. The program will prompt you to enter a canvas with `1` for black and `0` for white.
2. Each line represents a row of pixels.
3. Type `exit` when done, and the program will generate a `.bbt` image file.

### Example
For an image like this:

```
1 1 1
0 1 0
1 0 1
```

The output file will be a 3x3 image with black and white pixels arranged according to your input.

### Example Input:
```
--- BBT monochrome image creator ---
Black=>1
White=>0
type "exit" on new line to exit
max width is 255
1 1 1
0 1 0
1 0 1
exit
```

### Example Output:
- The program will create a file named `image.bbt` containing the image data.

### Error Handling
- The program checks for memory allocation failures.
- It ensures that the width of the image does not exceed 255 pixels.
- The input is trimmed of newline characters to ensure clean parsing.
