from conftest import PROMPT, get_command_output


def test_cd(shell_session):
    shell_session.sendline("cd /Users")
    shell_session.expect(PROMPT)
    shell_session.sendline("pwd")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "/Users" == result


def test_cd1(shell_session):
    shell_session.sendline("cd /Users/")
    shell_session.expect(PROMPT)
    shell_session.sendline("pwd")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "/Users" == result


def test_cd2(shell_session):
    shell_session.sendline("cd /")
    shell_session.expect(PROMPT)
    shell_session.sendline("pwd")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "/" == result
