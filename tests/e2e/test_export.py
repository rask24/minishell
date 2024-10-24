from conftest import PROMPT, get_command_output


def test_export_basic_variable(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("export TEST_VAR=value")
    shell_session.expect(PROMPT)
    shell_session.sendline("echo $TEST_VAR")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "value"


def test_export_update_variable(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("export TEST_VAR=old")
    shell_session.expect(PROMPT)
    shell_session.sendline("export TEST_VAR=new")
    shell_session.expect(PROMPT)
    shell_session.sendline("echo $TEST_VAR")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "new"


def test_export_no_value(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("export TEST_EMPTY")
    shell_session.expect(PROMPT)
    shell_session.sendline("export | grep TEST_EMPTY")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "declare -x TEST_EMPTY"
    assert '=""' not in result


def test_export_invalid_identifier(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("export 123invalid=value")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "minishell: export: `123invalid=value': not a valid identifier"
    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "1"


def test_export_no_key(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("export =value")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "minishell: export: `=value': not a valid identifier"
    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "1"


def test_export_multiple_variables(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("export VAR1=value1 VAR2=value2")
    shell_session.expect(PROMPT)
    shell_session.sendline("echo $VAR1,$VAR2")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "value1,value2"


def test_export_with_quotes(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline('export TEST_QUOTE="quoted value"')
    shell_session.expect(PROMPT)
    shell_session.sendline("echo $TEST_QUOTE")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "quoted value"


def test_export_list(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("export TEST_A=1")
    shell_session.expect(PROMPT)
    shell_session.sendline("export TEST_B=2")
    shell_session.expect(PROMPT)
    shell_session.sendline("export")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert 'declare -x TEST_A="1"' in result
    assert 'declare -x TEST_B="2"' in result


def test_export_special_chars(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("export TEST_SPECIAL='value!@#$%^'")
    shell_session.expect(PROMPT)
    shell_session.sendline("echo $TEST_SPECIAL")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "value!@#$%^"


def test_export_empty_value(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("export EMPTY=")
    shell_session.expect(PROMPT)
    shell_session.sendline("export | grep EMPTY")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert 'declare -x EMPTY=""' in result


def test_export_underscore_start(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("export _TEST=valid")
    shell_session.expect(PROMPT)
    shell_session.sendline("echo $_TEST")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "valid"


def test_export_invalid_chars(shell_session):
    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("export TEST@VAR=invalid")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "minishell: export: `TEST@VAR=invalid': not a valid identifier"
    shell_session.sendline("echo $?")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert result == "1"
