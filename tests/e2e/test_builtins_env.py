from conftest import PROMPT, get_command_output


def test_env_with_custom_var(shell_session):
    shell_session.sendline("export TEST_VAR=test_value")
    shell_session.expect(PROMPT)
    shell_session.sendline("env")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert "TEST_VAR=test_value" in result


def test_env_with_args(shell_session):
    shell_session.sendline("env arg1")
    shell_session.expect(PROMPT)
    error_output = get_command_output(shell_session.before)
    assert "minishell: env: too many arguments" == error_output
    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "1"


def test_env_after_unset(shell_session):
    shell_session.sendline("export TEMP_VAR=temp_value")
    shell_session.expect(PROMPT)
    shell_session.sendline("env")
    shell_session.expect(PROMPT)
    initial_result = get_command_output(shell_session.before)
    assert "TEMP_VAR=temp_value" in initial_result

    shell_session.sendline("unset TEMP_VAR")
    shell_session.expect(PROMPT)
    shell_session.sendline("env")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert "TEMP_VAR=temp_value" not in result


def test_env_invalid_value(shell_session):
    shell_session.sendline("export INVALID_VAR")
    shell_session.expect(PROMPT)
    shell_session.sendline("env")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert "INVALID_VAR=" not in result


def test_env_invalid_value1(shell_session):
    shell_session.sendline("export INVALID-VAR=value")
    shell_session.expect(PROMPT)
    shell_session.sendline("env")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert "INVALID-VAR=value" not in result


def test_env_multiple_exports(shell_session):
    shell_session.sendline("export VAR1=value1 VAR2=value2 VAR3=value3")
    shell_session.expect(PROMPT)
    shell_session.sendline("env")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert "VAR1=value1" in result
    assert "VAR2=value2" in result
    assert "VAR3=value3" in result


def test_env_update_existing(shell_session):
    shell_session.sendline("export TEST_VAR=old_value")
    shell_session.expect(PROMPT)
    shell_session.sendline("export TEST_VAR=new_value")
    shell_session.expect(PROMPT)
    shell_session.sendline("env")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert "TEST_VAR=new_value" in result
    assert "TEST_VAR=old_value" not in result
