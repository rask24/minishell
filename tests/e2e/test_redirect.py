import os

from conftest import PROMPT, get_command_output


def test_output_redirection(shell_session):
    test_file = "test_output_redirection.txt"

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
    test_file = "test_append_redirection.txt"

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
    test_file = "test_input_redirection.txt"
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
    input_file = "test_combined_redirection_input.txt"
    output_file = "test_combined_redirection_output.txt"

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
    file1 = "test_multiple_output_redirection1.txt"
    file2 = "test_multiple_output_redirection2.txt"
    file3 = "test_multiple_output_redirection3.txt"

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
    file1 = "test_multiple_input_redirection1.txt"
    file2 = "test_multiple_input_redirection2.txt"
    file3 = "test_multiple_input_redirection3.txt"

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


def test_only_redirection(shell_session):
    test_file1 = "test_only_redirection1.txt"
    test_file2 = "test_only_redirection2.txt"

    try:
        shell_session.sendline(f"> {test_file1} >> {test_file2}")
        shell_session.expect(PROMPT)

        assert os.path.exists(test_file1)
        assert os.path.exists(test_file2)
    finally:
        files = [test_file1, test_file2]
        for file in files:
            if os.path.exists(file):
                os.remove(file)


# FIXME
# def test_redirection_with_variable(shell_session):
#     test_file = "test_output.txt"

#     try:
#         shell_session.sendline(f"export OUTPUT={test_file}")
#         shell_session.sendline("echo Hello > $OUTPUT")
#         shell_session.expect(PROMPT)

#         assert os.path.exists(test_file)
#         with open(test_file, "r") as f:
#             assert f.read() == "Hello"
#     finally:
#         if os.path.exists(test_file):
#             os.remove(test_file)


def test_error_not_found_input_redirection(shell_session):
    test_file = "test_error_not_found_input_redirection.txt"

    shell_session.sendline(f"cat < {test_file}")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert result == f"minishell: {test_file}: No such file or directory"


# def test_error_permission_denied_output_redirection_with_variable(shell_session):
#     test_file = "test_output.txt"

#     try:
#         shell_session.sendline("export OUTPUT=test_output.txt")

#         assert os.path.exists(test_file)
#         os.chmod(test_file, 0o000)

#         shell_session.sendline(f"echo Hello > $OUTPUT")
#         shell_session.expect(PROMPT)

#         result = get_command_output(shell_session.before)

#         assert result == f"minishell: {test_file}: Permission denied"
#     finally:
#         if os.path.exists(test_file):
#             os.remove(test_file)


def test_error_permission_input_redirection(shell_session):
    test_file = "test_error_permission_input_redirection.txt"

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
    test_file1 = "test_error_permission_output_redirection1.txt"
    test_file2 = "test_error_permission_output_redirection2.txt"
    test_file3 = "test_error_permission_output_redirection3.txt"

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
    test_file = "test_error_redirection_and_builtin.txt"

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
    test_file = "test_error_redirection_and_spawn.txt"

    shell_session.sendline(f"cat < {test_file} && echo World")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert result == f"minishell: {test_file}: No such file or directory"


def test_error_ambiguous_redirection_wildcard(shell_session):
    test_name = "test_error_ambiguous_redirection_wildcard"
    test_file1 = f"{test_name}1.txt"
    test_file2 = f"{test_name}2.txt"
    test_file3 = f"{test_name}3.txt"

    try:
        with open(test_file1, "w") as f:
            f.write("Hello")
        with open(test_file2, "w") as f:
            f.write("World")
        with open(test_file3, "w") as f:
            f.write("42")

        shell_session.sendline(f"echo Tokyo > {test_name}*.txt")
        shell_session.expect(PROMPT)

        result = get_command_output(shell_session.before)
        assert result == f"minishell: {test_name}*.txt: ambiguous redirect"

    finally:
        files = [test_file1, test_file2, test_file3]
        for file in files:
            if os.path.exists(file):
                os.remove(file)


def test_error_only_redirection_permission_denied(shell_session):
    test_file = "test_error_only_redirection_permission_denied.txt"

    try:
        with open(test_file, "w") as f:
            f.write("Hello")
            os.chmod(test_file, 0o000)

            shell_session.sendline(f"> {test_file}")
            shell_session.expect(PROMPT)

            result = get_command_output(shell_session.before)
            assert result == f"minishell: {test_file}: Permission denied"
    finally:
        if os.path.exists(test_file):
            os.remove(test_file)


def test_pipeline_with_redirection(shell_session):
    test_file = "test_pipeline_with_redirection.txt"

    try:
        shell_session.sendline(f"/bin/echo Hello > {test_file} | /bin/cat")
        shell_session.expect(PROMPT)

        result = get_command_output(shell_session.before)
        assert result == ""

        with open(test_file, "r") as f:
            assert f.read() == "Hello\n"
    finally:
        if os.path.exists(test_file):
            os.remove(test_file)


def test_error_only_redirection_not_found(shell_session):
    test_file = "test_error_only_redirection_not_found.txt"

    shell_session.sendline(f"< {test_file}")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert result == f"minishell: {test_file}: No such file or directory"


def test_error_only_redirection_ambiguous(shell_session):
    shell_session.sendline("> ***")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert result == "minishell: ***: ambiguous redirect"


# TODO: Comment out after export is fixed
# def test_error_ambiguous_redirection_ifs(shell_session):
#     shell_session.sendline("export FILES='a b c'")
#     shell_session.sendline("echo Hello > $FILES")
#     shell_session.expect(PROMPT)


#     result = get_command_output(shell_session.before)
#     assert result == "minishell: $FILES: ambiguous redirect"


def test_subshell_output_redirection(shell_session):
    test_file = "test_subshell_output_redirection.txt"

    try:
        shell_session.sendline(f"(echo Hello) > {test_file}")
        shell_session.expect(PROMPT)

        assert os.path.exists(test_file)
        with open(test_file, "r") as f:
            assert f.read() == "Hello\n"
    finally:
        if os.path.exists(test_file):
            os.remove(test_file)


def test_subshell_both_side_redirection(shell_session):
    test_file1 = "test_subshell_both_side_redirection1.txt"
    test_file2 = "test_subshell_both_side_redirection2.txt"

    try:
        shell_session.sendline(f"(echo Hello > {test_file1}) > {test_file2}")
        shell_session.expect(PROMPT)

        assert os.path.exists(test_file1)
        with open(test_file1, "r") as f:
            assert f.read() == "Hello\n"

        assert os.path.exists(test_file2)
        with open(test_file2, "r") as f:
            assert f.read() == ""
    finally:
        for file in [test_file1, test_file2]:
            if os.path.exists(file):
                os.remove(file)


def test_subshell_both_side_redirection_pipeline(shell_session):
    test_file1 = "test_subshell_both_side_redirection_pipeline1.txt"
    test_file2 = "test_subshell_both_side_redirection_pipeline2.txt"

    try:
        shell_session.sendline(f"echo Hello | (cat > {test_file1}) > {test_file2}")
        shell_session.expect(PROMPT)

        assert os.path.exists(test_file1)
        with open(test_file1, "r") as f:
            assert f.read() == "Hello\n"

        assert os.path.exists(test_file2)
        with open(test_file2, "r") as f:
            assert f.read() == ""
    finally:
        for file in [test_file1, test_file2]:
            if os.path.exists(file):
                os.remove(file)
