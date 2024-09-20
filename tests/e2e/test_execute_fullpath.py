import os

from config import PROMPT, shell_session


def test_echo_command(shell_session):
    shell_session.sendline('/bin/echo "Hello, World!"')
    shell_session.expect("Hello, World!")
    shell_session.expect(PROMPT)
    assert "Hello, World!" in shell_session.before


def test_ls_command(shell_session):
    shell_session.sendline("/bin/ls -l")
    shell_session.expect(PROMPT)
    assert "total" in shell_session.before


def test_pwd_command(shell_session):
    shell_session.sendline("/bin/pwd")
    shell_session.expect(PROMPT)
    assert os.getcwd() in shell_session.before
