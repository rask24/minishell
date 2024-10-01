from conftest import PROMPT, get_command_output


def test_simple_heredoc(shell_session):
    shell_session.sendline("cat << EOF")
    shell_session.expect("> ")
    shell_session.sendline("Hello, world!")
    shell_session.expect("> ")
    shell_session.sendline("EOF")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert result == "Hello, world!"


def test_heredoc_many_inputs(shell_session):
    str = "a" * 512
    iters = 10

    shell_session.sendline("cat << EOF")
    for _ in range(iters):
        shell_session.expect("> ")
        shell_session.sendline(str)
    shell_session.expect("> ")
    shell_session.sendline("EOF")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert result == f"{str}\n" * (iters - 1) + str


# FIXME: This test is failing on github actions
# def test_warning_heredoc(shell_session):
#     shell_session.sendline("cat << EOF")
#     shell_session.expect("> ")
#     shell_session.sendline("Hello, world!")
#     shell_session.expect("> ")
#     shell_session.sendcontrol("D")
#     shell_session.expect(PROMPT)

#     result = get_command_output(shell_session.before)
#     assert (
#         result
#         == "minishell: warning: here-document delimited by end-of-file (wanted `EOF')\nHello, world!"
#     )
