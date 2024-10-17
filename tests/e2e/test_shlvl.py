from conftest import PROMPT, get_command_output


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

    INITIAL_SHLVL = 0
    recursive(shell_session, 1, INITIAL_SHLVL)


def test_shlvl_with_set_invalid_shlvl(shell_session):
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    shell_session.sendline("export SHLVL=invalid")
    shell_session.expect(PROMPT)

    INITIAL_SHLVL = 0
    recursive(shell_session, 1, INITIAL_SHLVL)


def test_shlvl_with_set_zero(shell_session):
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    shell_session.sendline("export SHLVL=0")
    shell_session.expect(PROMPT)

    INITIAL_SHLVL = 0
    recursive(shell_session, 1, INITIAL_SHLVL)


def test_shlvl_with_minus(shell_session):
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    shell_session.sendline("export SHLVL=-42")
    shell_session.expect(PROMPT)

    INITIAL_SHLVL = -1
    recursive(shell_session, 1, INITIAL_SHLVL)


def test_shlvl_with_plus_overflow(shell_session):
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    shell_session.sendline("export SHLVL=4242424242424242424242424242424242424242424242")
    shell_session.expect(PROMPT)

    INITIAL_SHLVL = 0
    recursive(shell_session, 1, INITIAL_SHLVL)


def test_shlvl_with_minus_overflow(shell_session):
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    shell_session.sendline("export SHLVL=-4242424242424242424242424242424242424242424242")
    shell_session.expect(PROMPT)

    INITIAL_SHLVL = 0
    recursive(shell_session, 1, INITIAL_SHLVL)


def test_shlvl_with_max(shell_session):
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    shell_session.sendline("export SHLVL=999")
    shell_session.expect(PROMPT)

    INITIAL_SHLVL = 0
    recursive(shell_session, 1, INITIAL_SHLVL)
