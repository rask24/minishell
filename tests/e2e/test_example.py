import os

import pexpect
import pytest

# Get the path to the minishell executable
PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "../.."))
MINISHELL_PATH = os.path.join(PROJECT_ROOT, "minishell")

prompt = "minishell$ "


@pytest.fixture
def minishell():
    # Spawn a new process
    child = pexpect.spawn(MINISHELL_PATH, encoding="utf-8")
    child.expect_exact(prompt)  # Wait for the prompt
    yield child
    child.close()


def test_hello(minishell):
    minishell.sendline("hello")
    minishell.expect_exact("hello")  # Check the output
    minishell.expect_exact(prompt)  # Wait for the prompt


def test_exit_on_ctrl_d(minishell):
    minishell.sendcontrol("d")
    minishell.expect_exact("exit")
    minishell.expect(pexpect.EOF)  # Check that the process has exited

    # Check the exit status
    assert minishell.exitstatus == 0
