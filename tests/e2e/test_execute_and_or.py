from conftest import PROMPT, get_command_output


def test_simple_and_success(shell_session):
    shell_session.sendline("echo Hello && echo World")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "Hello\nWorld" == result


def test_simple_and_fail(shell_session):
    shell_session.sendline("aaaaaaaaaaaaaaaaaaa && echo World")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "minishell: aaaaaaaaaaaaaaaaaaa: command not found" == result


def test_simple_or_success(shell_session):
    shell_session.sendline("echo Hello || echo World")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "Hello" == result


def test_simple_or_fail(shell_session):
    shell_session.sendline("aaaaaaaaaaaaaaaaaaa || echo World")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "minishell: aaaaaaaaaaaaaaaaaaa: command not found\nWorld" == result


def test_multiple_and(shell_session):
    shell_session.sendline("echo Hello && echo World && echo 42")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "Hello\nWorld\n42" == result


def test_multiple_or(shell_session):
    shell_session.sendline("aaaaaaaaaaaaaaaaaaa || echo World || echo 42")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "minishell: aaaaaaaaaaaaaaaaaaa: command not found\nWorld" == result


def test_mixed_and_or_success(shell_session):
    shell_session.sendline("echo Hello && echo World || echo 42")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "Hello\nWorld" == result


def test_mixed_and_or_fail(shell_session):
    shell_session.sendline("aaaaaaaaaaaaaaaaaaa && echo World || echo 42")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "minishell: aaaaaaaaaaaaaaaaaaa: command not found\n42" == result


def test_mixed_or_and_success(shell_session):
    shell_session.sendline("echo Hello || echo World && echo 42")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "Hello\n42" == result


def test_mixed_or_and_fail(shell_session):
    shell_session.sendline("aaaaaaaaaaaaaaaaaaa || echo World && echo 42")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "minishell: aaaaaaaaaaaaaaaaaaa: command not found\nWorld\n42" == result
