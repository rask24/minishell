import os
import subprocess

from conftest import PROMPT, get_command_output

# TODO: Add test for unset PATH
# TODO: Check exit status of the command


def test_full_pwd_command(shell_session):
    shell_session.sendline("/bin/pwd")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert os.getcwd() == result


def test_echo_command_from_path(shell_session):
    shell_session.sendline("echo Hello")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert result == "Hello"


def test_hostname_command_from_path(shell_session):
    shell_session.sendline("hostname")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert result == os.uname()[1]


def test_relative_shell_script(shell_session):
    test_file = "test_exec"

    try:
        with open(test_file, "w") as f:
            f.write("#!/bin/bash\necho Hello")
        os.chmod(test_file, 0o777)
        shell_session.sendline(f"./{test_file}")
        shell_session.expect(PROMPT)

        result = get_command_output(shell_session.before)
        assert result == "Hello"
    finally:
        if os.path.exists(test_file):
            os.remove(test_file)


def test_error_empty_command(shell_session):
    shell_session.sendline("''")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert result == "minishell: : command not found"


def test_error_dotdot(shell_session):
    shell_session.sendline("..")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert result == "minishell: ..: command not found"


def test_error_command_not_found(shell_session):
    shell_session.sendline("aaaaaaaaaaaaaaaaaaa")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert result == "minishell: aaaaaaaaaaaaaaaaaaa: command not found"


def test_error_relative_no_such_file_or_directory(shell_session):
    shell_session.sendline("./aaaaaaaaaaaaaaaaaaa")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert result == "minishell: ./aaaaaaaaaaaaaaaaaaa: No such file or directory"


def test_error_full_no_such_file_or_directory(shell_session):
    shell_session.sendline("/bin/aaaaaaaaaaaaaaaaaaa")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert result == "minishell: /bin/aaaaaaaaaaaaaaaaaaa: No such file or directory"


def test_error_is_a_directory(shell_session):
    shell_session.sendline("/bin")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert result == "minishell: /bin: Is a directory"


def test_error_permission_denied(shell_session):
    test_file = "test_exec"

    try:
        with open(test_file, "w") as f:
            f.write("#!/bin/bash\necho Hello")
        os.chmod(test_file, 0o666)
        shell_session.sendline(f"./{test_file}")
        shell_session.expect(PROMPT)

        result = get_command_output(shell_session.before)
        assert result == f"minishell: ./{test_file}: Permission denied"
    finally:
        if os.path.exists(test_file):
            os.remove(test_file)


# os.symlink() and os.remove() are not working as expected
# so we use subprocess to create and remove symbolic links
def test_error_too_many_levels_symbolic_links(shell_session):
    test_file1 = "test_exec1"
    test_file2 = "test_exec2"

    try:
        subprocess.run(["ln", "-sf", test_file1, test_file2], check=True)
        subprocess.run(["ln", "-sf", test_file2, test_file1], check=True)

        shell_session.sendline(f"./{test_file1}")
        shell_session.expect(PROMPT)

        result = get_command_output(shell_session.before)
        assert result == f"minishell: ./{test_file1}: Too many levels of symbolic links"
    finally:
        for file in [test_file1, test_file2]:
            subprocess.run(["rm", "-f", file], check=True)


# It is not neccessary to create a test file
def test_error_file_name_too_long(shell_session):
    length = 1000
    test_file = "a" * length

    shell_session.sendline(f"./{test_file}")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert result == f"minishell: ./{test_file}: File name too long"
