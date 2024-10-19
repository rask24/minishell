from conftest import PROMPT, get_command_output


def check_shlvl_increment_recursively(shell_session, i, initial_shlvl):
    if i == 2:
        shell_session.sendline("exit")
        return

    shell_session.sendline("./minishell")
    shell_session.expect(PROMPT)
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)

    str = get_command_output(shell_session.before)
    print(str)
    current_shlvl = int(str)

    assert current_shlvl == (i + initial_shlvl)
    check_shlvl_increment_recursively(shell_session, i + 1, initial_shlvl)


def test_shlvl_many_times(shell_session):
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    initial_shlvl = int(get_command_output(shell_session.before))

    check_shlvl_increment_recursively(shell_session, 1, initial_shlvl)


def test_shlvl_with_unset_shlvl(shell_session):
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    shell_session.sendline("unset SHLVL")
    shell_session.expect(PROMPT)

    initial_shlvl = 0
    check_shlvl_increment_recursively(shell_session, 1, initial_shlvl)


def test_shlvl_with_set_invalid_shlvl(shell_session):
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    shell_session.sendline("export SHLVL=invalid")
    shell_session.expect(PROMPT)

    initial_shlvl = 0
    check_shlvl_increment_recursively(shell_session, 1, initial_shlvl)


def test_shlvl_with_set_zero(shell_session):
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    shell_session.sendline("export SHLVL=0")
    shell_session.expect(PROMPT)

    initial_shlvl = 0
    check_shlvl_increment_recursively(shell_session, 1, initial_shlvl)


def test_shlvl_with_minus(shell_session):
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    shell_session.sendline("export SHLVL=-42")
    shell_session.expect(PROMPT)

    initial_shlvl = -1
    check_shlvl_increment_recursively(shell_session, 1, initial_shlvl)


def test_shlvl_with_plus_overflow(shell_session):
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    shell_session.sendline("export SHLVL=4242424242424242424242424242424242424242424242")
    shell_session.expect(PROMPT)

    initial_shlvl = 0
    check_shlvl_increment_recursively(shell_session, 1, initial_shlvl)


def test_shlvl_with_minus_overflow(shell_session):
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    shell_session.sendline("export SHLVL=-4242424242424242424242424242424242424242424242")
    shell_session.expect(PROMPT)

    initial_shlvl = 0
    check_shlvl_increment_recursively(shell_session, 1, initial_shlvl)


def test_shlvl_with_max(shell_session):
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    shell_session.sendline("export SHLVL=999")
    shell_session.expect(PROMPT)

    initial_shlvl = 0
    check_shlvl_increment_recursively(shell_session, 1, initial_shlvl)


def test_shlvl_with_max_minus_one(shell_session):
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    shell_session.sendline("export SHLVL=998")
    shell_session.expect(PROMPT)

    initial_shlvl = 998
    check_shlvl_increment_recursively(shell_session, 1, initial_shlvl)


def test_shlvl_with_fourtytwo(shell_session):
    shell_session.sendline("echo $SHLVL")
    shell_session.expect(PROMPT)
    shell_session.sendline("export SHLVL=42")
    shell_session.expect(PROMPT)

    initial_shlvl = 42
    check_shlvl_increment_recursively(shell_session, 1, initial_shlvl)
