import os
from codecs import ascii_encode

from conftest import PROMPT, get_command_output


def test_output_redirection(shell_session):
    test_file = "test_output.txt"

    try:
        shell_session.sendline(f"echo Output! > {test_file}")
        shell_session.expect(PROMPT)

        assert os.path.exists(test_file)
        with open(test_file, "r") as f:
            assert f.read() == "Output!\n"
    finally:
        if os.path.exists(test_file):
            os.remove(test_file)


def test_append_redirection(shell_session):
    test_file = "test_append.txt"

    try:
        shell_session.sendline(f"echo Line1 > {test_file}")
        shell_session.expect(PROMPT)
        shell_session.sendline(f"echo Line2 >> {test_file}")
        shell_session.expect(PROMPT)

        with open(test_file, "r") as f:
            content = f.read()
            assert content == "Line1\nLine2\n"
    finally:
        if os.path.exists(test_file):
            os.remove(test_file)


def test_input_redirection(shell_session):
    test_file = "test_input.txt"
    try:
        shell_session.sendline(f"echo Input! > {test_file}")
        shell_session.expect(PROMPT)
        shell_session.sendline(f"cat < {test_file}")
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
        shell_session.sendline(f"echo Combined! > {input_file}")
        shell_session.expect(PROMPT)
        shell_session.sendline(f"cat < {input_file} > {output_file}")
        shell_session.expect(PROMPT)

        with open(output_file, "r") as f:
            assert f.read() == "Combined!\n"
    finally:
        for file in [input_file, output_file]:
            if os.path.exists(file):
                os.remove(file)


def test_multiple_output_redirection(shell_session):
    file1 = "test_output1.txt"
    file2 = "test_output2.txt"
    file3 = "test_output3.txt"

    try:
        shell_session.sendline(f"> {file1} echo Hello > {file2} > {file3}")
        shell_session.expect(PROMPT)

        assert os.path.exists(file1)
        with open(file1, "r") as f:
            assert f.read() == ""

        assert os.path.exists(file2)
        with open(file2, "r") as f:
            assert f.read() == ""

        assert os.path.exists(file3)
        with open(file3, "r") as f:
            assert f.read() == "Hello\n"
    finally:
        for file in [file1, file2, file3]:
            if os.path.exists(file):
                os.remove(file)


def test_multiple_input_redirection(shell_session):
    file1 = "test_input1.txt"
    file2 = "test_input2.txt"
    file3 = "test_input3.txt"

    try:
        shell_session.sendline(f"echo Hello > {file1}")
        shell_session.expect(PROMPT)
        shell_session.sendline(f"echo World > {file2}")
        shell_session.expect(PROMPT)
        shell_session.sendline(f"echo 42 > {file3}")
        shell_session.expect(PROMPT)
        shell_session.sendline(f" < {file1} cat < {file2} < {file3}")
        shell_session.expect(PROMPT)

        result = get_command_output(shell_session.before)
        assert result == "42"
    finally:
        for file in [file1, file2, file3]:
            if os.path.exists(file):
                os.remove(file)


def test_error_not_found_input_redirection(shell_session):
    test_file = "not_found.txt"

    shell_session.sendline(f"cat < {test_file}")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert result == f"minishell: {test_file}: No such file or directory"


def test_error_permission_input_redirection(shell_session):
    test_file = "test_output.txt"

    try:
        with open(test_file, "w") as f:
            f.write("Hello")
            os.chmod(test_file, 0o000)

            shell_session.sendline(f"cat < {test_file}")
            shell_session.expect(PROMPT)

            result = get_command_output(shell_session.before)
            assert result == f"minishell: {test_file}: Permission denied"
    finally:
        if os.path.exists(test_file):
            os.remove(test_file)


def test_error_permission_output_redirection(shell_session):
    test_file1 = "test_output1.txt"
    test_file2 = "test_output2.txt"
    test_file3 = "test_output3.txt"

    try:
        with open(test_file2, "w") as f:
            f.write("Hello")
            os.chmod(test_file2, 0o000)

            shell_session.sendline(f"echo Hello > {test_file1} > {test_file2} > {test_file3}")
            shell_session.expect(PROMPT)

            result = get_command_output(shell_session.before)
            assert result == f"minishell: {test_file2}: Permission denied"

            assert os.path.exists(test_file1)
            with open(test_file1, "r") as f:
                assert f.read() == ""

            assert not os.path.exists(test_file3)
    finally:
        for file in [test_file1, test_file2, test_file3]:
            if os.path.exists(file):
                os.remove(file)


def test_error_redirection_and_builtin(shell_session):
    test_file = "test_output.txt"

    try:
        with open(test_file, "w") as f:
            f.write("Hello")
            os.chmod(test_file, 0o000)

            shell_session.sendline(f"echo Hello > {test_file} && echo World")
            shell_session.expect(PROMPT)

            result = get_command_output(shell_session.before)
            assert result == f"minishell: {test_file}: Permission denied"
    finally:
        if os.path.exists(test_file):
            os.remove(test_file)


def test_error_redirection_and_spawn(shell_session):
    test_file = "test.txt"

    shell_session.sendline(f"cat < {test_file} && echo World")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert result == f"minishell: {test_file}: No such file or directory"


def test_error_ambiguous_redirection_wildcard(shell_session):
    test_file1 = "test_output1.txt"
    test_file2 = "test_output2.txt"
    test_file3 = "test_output3.txt"

    try:
        with open(test_file1, "w") as f:
            f.write("Hello")
        with open(test_file2, "w") as f:
            f.write("World")
        with open(test_file3, "w") as f:
            f.write("42")

        shell_session.sendline("echo Tokyo > test_output*.txt")
        shell_session.expect(PROMPT)

        result = get_command_output(shell_session.before)
        assert result == "minishell: test_output*.txt: ambiguous redirect"

    finally:
        files = [test_file1, test_file2, test_file3]
        for file in files:
            if os.path.exists(file):
                os.remove(file)


# FiXME: Comment out after export is fixed
# def test_error_ambiguous_redirection_ifs(shell_session):
#     shell_session.sendline("export FILES='a b c'")
#     shell_session.sendline("echo Hello > $FILES")
#     shell_session.expect(PROMPT)

#     result = get_command_output(shell_session.before)
#     assert result == "minishell: $FILES: ambiguous redirect"
