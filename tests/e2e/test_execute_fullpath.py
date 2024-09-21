import os

from conftest import PROMPT, get_command_output


def test_echo_command(shell_session):
    shell_session.sendline("/bin/echo Hello")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert result == "Hello"


def test_ls_command(shell_session):
    shell_session.sendline("/bin/ls -l")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "total" in result


def test_pwd_command(shell_session):
    shell_session.sendline("/bin/pwd")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert os.getcwd() == result
