from conftest import PROMPT, get_command_output


def test_exit_no_args_after_cmd(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("cd")
    shell_session.expect("")
    shell_session.sendline("exit")
    shell_session.expect("exit")
    shell_session.expect(PROMPT)
    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "0"


def test_exit_no_args_after_failed_cmd(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("cd /nonexistent")
    shell_session.expect("")
    shell_session.sendline("exit")
    shell_session.expect("exit")
    shell_session.expect(PROMPT)
    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "1"


def test_exit_with_status(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("exit 42")
    shell_session.expect("exit")
    shell_session.expect(PROMPT)
    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "42"


def test_exit_with_invalid_number(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("exit abc")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "exit\nminishell: exit: abc: numeric argument required"
    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "2"


def test_exit_with_too_large_number(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("exit 999999999999999999999999")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "exit\nminishell: exit: 999999999999999999999999: numeric argument required"
    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "2"


def test_exit_with_negative(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("exit -1")
    shell_session.expect("exit")
    shell_session.expect(PROMPT)
    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "255"


def test_exit_with_dash_dash(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("exit -- 42")
    shell_session.expect("exit")
    shell_session.expect(PROMPT)
    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "42"


def test_exit_too_many_args(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("exit 4 2")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "exit\nminishell: exit: too many arguments"
    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "1"


def test_exit_too_many_args_with_dash_dash(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("exit -- 4 2")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "exit\nminishell: exit: too many arguments"
    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "1"


def test_exit_with_leading_plus(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("exit +42")
    shell_session.expect("exit")
    shell_session.expect(PROMPT)
    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "42"


def test_exit_with_status_overflow(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("exit 298")
    shell_session.expect("exit")
    shell_session.expect(PROMPT)
    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "42"  # 298 % 256 = 42


def test_exit_with_mixed_valid_invalid(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("exit 42abc")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "exit\nminishell: exit: 42abc: numeric argument required"
    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "2"
