*This project has been created as part of the 42 curriculum by nfaronia.*

# fract-ol

## 📝 Description
**fract-ol** is a graphical program that visualizes fractals, specifically the Mandelbrot and Julia sets.
The program allows interactive exploration of these fractals, including zooming, and changing parameters for Julia sets.

## 📌 Instructions

### 🛠️ Compilation
To compile the project, run:
```
make
```
This will generate the executable `fractol`.
Dependencies:
- `MiniLibX` library

### 💻 Execution
Run the program with one of the following options:
**Mandelbrot set**:
```
./fractol mandelbrot
```
**Julia set**:
```
./fractol julia
./fractol julia <real_part> <imaginary_part>
```
- If no parameters are provided for Julia, it uses default values.

**Controls** (default with MiniLibX):
- Mouse scroll: Zoom in/out
- Arrow keys: Move the view
- ESC key: Exit program

## 🗃️ Resources

### 📚 References
- 42 minitalk subject
- MiniLibX
  - [MiniLibX docs42](https://harm-smits.github.io/42docs/libs/minilibx)
  - [Basic introduction](https://gontjarow.github.io/MiniLibX/)
- [fractol](https://www.geeksforgeeks.org/computer-graphics/fractals-in-cc/)
- [Mandelbrot](https://www.geeksforgeeks.org/cpp/mandlebrot-set-in-c-c-using-graphics/)
- Julia
  - [Julia Examples](https://paulbourke.net/fractals/juliaset/)
  - [Implementation](https://rosettacode.org/wiki/Julia_set)

### 🤖 AI Usage

AI tools were used as a learning aid to help find study resources, understand algorithms, and clarify edge cases.
