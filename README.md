# Assembler-Disassembler

This project is a mini-LC4 Assembler-Disassembler implemented in the C programming language. The assembly program reads in assembly language code from a text file (.ASM) and generates its machine equivalent in the form of a binary file (.OBJ). The assembler follows the file-oriented approach of C, treating files as I/O devices. The disassembler will open and read in a .OBJ file created by PennSim, parse it, and load it into a linked list that will represent the LC4’s program and data memories.

## Features of Assembler-Disassembler

The Assembler-Disassembler project offers the following features:

1. **Text File Input**: The program reads assembly language code from a text file (.ASM) or (.OBJ) as input.

2. **Binary or Assembly File Output**: Assembler program generates a binary file (.OBJ) containing the machine code equivalent of the input assembly language. The disassembler program generates the label, address, contents, and assembly of the (.OBJ) file.

3. **Support for Text and Binary Files**: The program handles both text and binary files, distinguishing between the two categories.

4. **PennSim Compatibility**: The generated .OBJ file is compatible with PennSim, a simulator for the LC4 architecture.

5. **Conversion to Machine Code**: The assembler converts assembly language instructions into their machine code representations according to the LC4 instruction set architecture.


## Example of Assembler

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
