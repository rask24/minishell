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


def test_pipeline_with_redirection(shell_session):
    test_file = "test_output.txt"

    try:
        shell_session.sendline(f"/bin/echo Hello > {test_file} | /bin/cat")
        shell_session.expect(PROMPT)

        result = get_command_output(shell_session.before)
        assert result == ""

        with open(test_file, "r") as f:
            assert f.read() == "Hello\n"
    finally:
        if os.path.exists(test_file):
            os.remove(test_file)


def test_pipeline_many_commands(shell_session):
    pipe_command = "echo Hello"
    for _ in range(1000):
        pipe_command += " | cat"
    shell_session.sendline(pipe_command)
    shell_session.expect(PROMPT)

    result = get_command_output(shell_session.before)
    assert "Hello" == result
