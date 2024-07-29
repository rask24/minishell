# Minishell

A simple shell implementation project.

[![Codecov](https://codecov.io/gh/rask24/minishell/branch/main/graph/badge.svg)](https://codecov.io/gh/rask24/minishell)

## Installation

Clone the repository with submodules:

```bash
git clone --recursive https://github.com/rask24/minishell.git
```

## Build Rules

The project uses a Makefile with the following main rules:

- `make all`: Builds the minishell executable
- `make clean`: Removes object files
- `make fclean`: Removes object files and the executable
- `make re`: Rebuilds the project from scratch
- `make test`: Runs unit tests
- `make coverage`: Generates code coverage data
- `make report_coverage`: Generates and displays the code coverage report
- `make norm`: Runs the Norminette code style checker

## Usage

To build and run the minishell:

```bash
make
./minishell
```

## Testing

To run the unit tests:

```bash
make test
```

To generate a code coverage report:

```bash
make coverage
make report_coverage
```

To run the end-to-end tests:

```bash
# Ensure you are using Python 3.12.4
python3 --version

# Install required Python packages
pip install -r tests/e2e/requirements.txt

# Run the tests
pytest tests/e2e
```

## Dependencies

This project requires:

- GCC
- Make
- Python 3 (for end-to-end tests)
