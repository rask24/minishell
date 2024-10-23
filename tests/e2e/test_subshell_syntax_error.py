from conftest import PROMPT, get_command_output


def test_error_subshell_with_missing_closing_parenthesis(shell_session):
    shell_session.sendline("(echo Hello")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert "minishell: syntax error near unexpected token `EOF'" == result


def test_error_subshell_with_extra_closing_parenthesis(shell_session):
    shell_session.sendline("(echo Hello))")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert "minishell: syntax error near unexpected token `)'" == result


def test_error_subshell_with_unmatched_opening_parenthesis(shell_session):
    shell_session.sendline("(echo Hello) (echo World)")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert "minishell: syntax error near unexpected token `('" == result


def test_error_subshell_with_misplaced_pipe(shell_session):
    shell_session.sendline("(echo Hello |)")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert "minishell: syntax error near unexpected token `)'" == result


def test_error_nested_subshell_with_error(shell_session):
    shell_session.sendline("(echo Hello (echo nested)")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert "minishell: syntax error near unexpected token `('" == result


def test_error_empty_subshell(shell_session):
    shell_session.sendline("()")
    shell_session.expect(PROMPT)
    result = get_command_output(shell_session.before)
    assert "minishell: syntax error near unexpected token `)'" == result


def test_error_subshell_after_cmd(shell_session):
    shell_session.sendline("echo Hello (ls)")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "minishell: syntax error near unexpected token `('" == result
