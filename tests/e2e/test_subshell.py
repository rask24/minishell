from conftest import PROMPT, get_command_output


def test_simple_subshell(shell_session):
    shell_session.sendline("(echo Hello)")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "Hello" == result


def test_subshell_with_pipeline(shell_session):
    shell_session.sendline("(echo Hello) | ((cat) | (cat -e))")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "Hello$" == result
