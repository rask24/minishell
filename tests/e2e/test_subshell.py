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


def recursive(shell_session, i, INITIAL_SHLVL):
    if i == 4:
        shell_session.sendline("exit")
        return

    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    current_shlvl = int(get_command_output(shell_session.before))
    assert current_shlvl == (i + INITIAL_SHLVL)
    recursive(shell_session, i + 1, INITIAL_SHLVL)


def test_shlvl_many_times(shell_session):
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    INITIAL_SHLVL = int(get_command_output(shell_session.before))

    recursive(shell_session, 1, INITIAL_SHLVL)


def test_shlvl_with_unset_shlvl(shell_session):
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    shell_session.sendline("unset SHLVL")
    shell_session.expect(PROMPT)

    recursive(shell_session, 1, 0)


def test_shlvl_with_set_invalid_shlvl(shell_session):
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    shell_session.sendline("export SHLVL=invalid")
    shell_session.expect(PROMPT)

    recursive(shell_session, 1, 0)
