import os

from conftest import PROMPT, get_command_output


def test_cd(shell_session):
    shell_session.sendline("cd /home")
    shell_session.expect(PROMPT)
    shell_session.sendline("pwd")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "/home" == result


def test_cd1(shell_session):
    shell_session.sendline("cd /home/")
    shell_session.expect(PROMPT)
    shell_session.sendline("pwd")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "/home" == result


def test_cd2(shell_session):
    shell_session.sendline("cd /")
    shell_session.expect(PROMPT)
    shell_session.sendline("pwd")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "/" == result


def test_cd_remove_one_dot(shell_session):
    shell_session.sendline("cd ./src/./")
    shell_session.expect(PROMPT)
    shell_session.sendline("pwd")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)

    expected_path = os.path.join(os.getcwd(), "src")
    assert expected_path == result


def test_cd_remove_two_dots(shell_session):
    shell_session.sendline("cd ./src/../")
    shell_session.expect(PROMPT)
    shell_session.sendline("pwd")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)

    expected_path = os.getcwd()
    assert expected_path == result


def test_cd_remove_many_two_dots(shell_session):
    shell_session.sendline("cd ../../../../../../../../../../")
    shell_session.expect(PROMPT)
    shell_session.sendline("pwd")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert "/" == result


def test_cd_remove_many_two_dots_then_path(shell_session):
    shell_session.sendline("cd ../../../../../../../../../../home")
    shell_session.expect(PROMPT)
    shell_session.sendline("pwd")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert "/home" == result


def test_cd_home(shell_session):
    shell_session.sendline("cd")
    shell_session.expect(PROMPT)
    shell_session.sendline("pwd")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)

    assert os.environ["HOME"] == result


def test_cd_error_nonexistent(shell_session):
    shell_session.sendline("cd /nonexistent_directory")
    shell_session.expect(PROMPT)
    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "1"


def test_cd_error_too_many_args(shell_session):
    shell_session.sendline("cd /usr /var")
    shell_session.expect(PROMPT)
    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "1"


def test_cd_no_home_set(shell_session):
    shell_session.sendline("export HOME_BAK=$HOME")
    shell_session.expect(PROMPT)
    try:
        shell_session.sendline("unset HOME")
        shell_session.expect(PROMPT)
        shell_session.sendline("cd")
        shell_session.expect(PROMPT)
        shell_session.sendline("echo $?")
        shell_session.expect(PROMPT)
        result = get_command_output(shell_session.before)
        assert result == "1"
    finally:
        shell_session.sendline("export HOME=$HOME_BAK")
        shell_session.expect(PROMPT)


def test_cd_many_slashes(shell_session):
    shell_session.sendline("cd /////usr////local////")
    shell_session.expect(PROMPT)
    shell_session.sendline("pwd")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "/usr/local"


def test_cd_error_permission_denied(shell_session):
    if os.path.exists("/root"):
        shell_session.sendline("cd /root")
        shell_session.expect(PROMPT)
        shell_session.sendline("echo $?")
        shell_session.expect(PROMPT)
        result = get_command_output(shell_session.before)
        assert result == "1"


def test_cd_error_permission_denied1(shell_session):
    shell_session.sendline("mkdir test_no_access")
    shell_session.expect(PROMPT)

    shell_session.sendline("chmod 000 test_no_access")
    shell_session.expect(PROMPT)

    shell_session.sendline("cd test_no_access")
    shell_session.expect(PROMPT)

    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "1"

    shell_session.sendline("chmod 755 test_no_access")
    shell_session.expect(PROMPT)

    shell_session.sendline("rmdir test_no_access")
    shell_session.expect(PROMPT)
