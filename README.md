# Pipex Project
## Overview
The pipex project is a 42 school assignment that aims to recreate the behavior of shell pipelines. This project involves creating a program that can replicate the functionality of Unix pipes, handling multiple commands and their respective input and output redirections.

## Features
- **Command Execution**: Executes commands in a pipeline, replicating the behavior of shell pipelines.
- **Here Document**: Supports here-document functionality, allowing multiple lines of input to be treated as a single string until a specified delimiter is reached.
- **Error Handling**: Provides robust error handling for invalid arguments, command not found, permission issues, and other runtime errors.
- **Quote and Escape Handling**: Correctly processes single quotes, double quotes, and backslashes, ensuring proper execution of commands with special characters.

## Installation
To build the project, navigate to the project directory and run the following command:

```sh
make
```
This will compile the project and generate the pipex executable.

## Usage
The pipex program can be used in two primary ways:

### File Input and Output

```sh
./pipex file1 cmd1 cmd2 ... file2
```
file1: The input file.\
cmd1, cmd2, ...: The commands to execute.\
file2: The output file.

Example:

```sh
./pipex infile "ls -l" "wc -l" outfile
```

Equivalent Bash command:
```sh
< infile ls -l | wc -l > outfile
```

### Here Document

```sh
./pipex here_doc LIMITER cmd1 cmd2 ... file
```
LIMITER: The delimiter string for here document. \
cmd1, cmd2, ...: The commands to execute. \
file: The output file. \

Example:

```sh
./pipex here_doc EOF "cat" "grep 'Hello World'" outfile
```

Equivalent Bash command:
```sh
cat << EOF | grep 'Hello World' > outfile
```

## Error Handling
The pipex program provides detailed error messages for various scenarios, including:

- Invalid number of arguments.
- Command not found.
- Permission denied.
- File not found.
- System call failures.
- Memory allocation failures.
- Quotation errors.

## Development
### Prerequisites
Make sure you have a C compiler (gcc or clang) installed.
The make utility is required to build the project.

Building the Project
To build the project, run:

```sh
make
```
### Running Tests
Unit tests are written using the gtest framework. To run the tests:

```sh
make test
```
### Cleaning Up
To clean up the compiled files:

```sh
make clean
```

## License
This project is licensed under the MIT License - see the LICENSE file for details.
