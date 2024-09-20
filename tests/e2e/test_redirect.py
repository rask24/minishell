import os

from conftest import PROMPT, get_command_output


def test_output_redirection(shell_session):
    test_file = "test_output.txt"

    try:
        shell_session.sendline(f"/bin/echo Output! > {test_file}")
        shell_session.expect(PROMPT)

        assert os.path.exists(test_file), f"Failed to create the file: {test_file}"
        with open(test_file, "r") as f:
            assert f.read().strip() == "Output!", "File content doesn't match expected output"
    finally:
        if os.path.exists(test_file):
            os.remove(test_file)


def test_append_redirection(shell_session):
    test_file = "test_append.txt"

    try:
        shell_session.sendline(f"/bin/echo Line1 > {test_file}")
        shell_session.expect(PROMPT)
        shell_session.sendline(f"/bin/echo Line2 >> {test_file}")
        shell_session.expect(PROMPT)

        with open(test_file, "r") as f:
            content = f.read().strip()
            assert content == "Line1\nLine2", "File content doesn't match expected output"
    finally:
        if os.path.exists(test_file):
            os.remove(test_file)


def test_input_redirection(shell_session):
    test_file = "test_input.txt"
    try:
        shell_session.sendline(f"/bin/echo Input! > {test_file}")
        shell_session.expect(PROMPT)
        shell_session.sendline(f"/bin/cat < {test_file}")
        shell_session.expect(PROMPT)

        result = get_command_output(shell_session.before)
        assert result == "Input!"
    finally:
        if os.path.exists(test_file):
            os.remove(test_file)


def test_combined_redirection(shell_session):
    input_file = "test_input.txt"
    output_file = "test_output.txt"

    try:
        shell_session.sendline(f"/bin/echo Combined! > {input_file}")
        shell_session.expect(PROMPT)
        shell_session.sendline(f"/bin/cat < {input_file} > {output_file}")
        shell_session.expect(PROMPT)

        with open(output_file, "r") as f:
            assert f.read().strip() == "Combined!", "File content doesn't match expected output"
    finally:
        for file in [input_file, output_file]:
            if os.path.exists(file):
                os.remove(file)


def test_multiple_output_redirection(shell_session):
    file1 = "test_output1.txt"
    file2 = "test_output2.txt"
    file3 = "test_output3.txt"

    try:
        shell_session.sendline(f"> {file1} /bin/echo Hello > {file2} > {file3}")
        shell_session.expect(PROMPT)

        assert os.path.exists(file1), f"Failed to create the file: {file1}"
        with open(file1, "r") as f:
            assert f.read().strip() == "", f"Content of {file1} doesn't match expected output"

        assert os.path.exists(file2), f"Failed to create the file: {file2}"
        with open(file2, "r") as f:
            assert f.read().strip() == "", f"Content of {file2} doesn't match expected output"

        assert os.path.exists(file3), f"Failed to create the file: {file3}"
        with open(file3, "r") as f:
            assert f.read().strip() == "Hello", f"Content of {file3} doesn't match expected output"
    finally:
        for file in [file1, file2, file3]:
            if os.path.exists(file):
                os.remove(file)


def test_multiple_input_redirection(shell_session):
    file1 = "test_input1.txt"
    file2 = "test_input2.txt"
    file3 = "test_input3.txt"

    try:
        shell_session.sendline(f"/bin/echo Hello > {file1}")
        shell_session.expect(PROMPT)
        shell_session.sendline(f"/bin/echo World > {file2}")
        shell_session.expect(PROMPT)
        shell_session.sendline(f"/bin/echo 42 > {file3}")
        shell_session.expect(PROMPT)
        shell_session.sendline(f" < {file1} /bin/cat < {file2} < {file3}")
        shell_session.expect(PROMPT)

        result = get_command_output(shell_session.before)
        assert result == "42"
    finally:
        for file in [file1, file2, file3]:
            if os.path.exists(file):
                os.remove(file)
