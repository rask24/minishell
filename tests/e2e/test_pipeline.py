import os

from conftest import PROMPT, get_command_output


def test_simple_pipeline(shell_session):
    shell_session.sendline("/bin/echo Hello | /bin/cat")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "Hello" == result


def test_multiple_pipeline(shell_session):
    shell_session.sendline("/bin/echo Hello | /bin/cat -e | /bin/cat | /usr/bin/tail -c 4")
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "lo$" == result


def test_pipeline_many_commands(shell_session):
    pipe_command = "echo Hello"

    if os.uname().sysname == "Darwin":
        num_pipes = 300
    else:
        num_pipes = 1000

    for _ in range(num_pipes):
        pipe_command += " | cat"
    shell_session.sendline(pipe_command)
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "Hello" == result
