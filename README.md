# Assembler-Disassembler

# LC4 Assembler

This project is a mini-LC4 Assembler implemented in the C programming language. It reads in assembly language code from a text file (.ASM) and generates its machine equivalent in the form of a binary file (.OBJ). The assembler follows the file-oriented approach of C, treating files as I/O devices.

## Features

The LC4 Assembler project offers the following features:

1. **Text File Input**: The program reads assembly language code from a text file (.ASM) as input.

2. **Binary File Output**: It generates a binary file (.OBJ) containing the machine code equivalent of the input assembly language.

3. **Support for Text and Binary Files**: The program handles both text and binary files, distinguishing between the two categories.

4. **PennSim Compatibility**: The generated .OBJ file is compatible with PennSim, a simulator for the LC4 architecture.

5. **Conversion to Machine Code**: The assembler converts assembly language instructions into their machine code representations according to the LC4 instruction set architecture.

## Getting Started

To get started with the LC4 Assembler, follow these steps:

1. Clone the repository:

   ```
   git clone https://github.com/bpantha/Assembler
   ```

2. Compile the source code using Makefile:

   ```
   make all
   ```

3. Execute the program, providing the input assembly file as a command-line argument:

   ```
   ./lc4_assembler input.asm
   ```

   This will generate the corresponding binary file, `input.obj`, in the current directory.

## Example

Suppose we have an assembly file named `example.asm` with the following content:

```
.ORIG x3000
LD R0, VALUE
LEA R1, MESSAGE
PUTS
HALT
VALUE .FILL x1234
MESSAGE .STRINGZ "Hello, World!"
.END
```

Running the LC4 Assembler on this input file will produce the binary file `example.obj`, containing the machine code representation of the assembly program.

## Contributing

Contributions to the LC4 Assembler project are welcome. If you find any issues or have suggestions for improvements, please feel free to submit a pull request or create an issue in the GitHub repository.

## License

This project is licensed under the [MIT License](LICENSE).
