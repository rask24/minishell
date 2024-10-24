from conftest import PROMPT, get_command_output


def test_unset_single_var(shell_session):
    shell_session.sendline("export TEST_VAR=value")
    shell_session.expect(PROMPT)

    shell_session.sendline("echo $TEST_VAR")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "value"

    shell_session.sendline("unset TEST_VAR")
    shell_session.expect(PROMPT)

    shell_session.sendline("echo $TEST_VAR")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == ""


def test_unset_multiple_vars(shell_session):
    shell_session.sendline("export VAR1=value1 VAR2=value2 VAR3=value3")
    shell_session.expect(PROMPT)

    shell_session.sendline("unset VAR1 VAR2 VAR3")
    shell_session.expect(PROMPT)

    shell_session.sendline("echo $VAR1$VAR2$VAR3")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == ""


def test_unset_nonexistent_var(shell_session):
    shell_session.sendline("unset NONEXISTENT_VAR")
    shell_session.expect(PROMPT)

    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "0"


def test_unset_path_var(shell_session):
    shell_session.sendline("echo $PATH")
    shell_session.expect(PROMPT)
    shell_session.sendline("unset PATH")
    shell_session.expect(PROMPT)

    shell_session.sendline("echo $PATH")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == ""


def test_unset_empty_args(shell_session):
    shell_session.sendline("unset")
    shell_session.expect(PROMPT)

    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "0"
