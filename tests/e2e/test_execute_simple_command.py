import os

from conftest import PROMPT, get_command_output


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
