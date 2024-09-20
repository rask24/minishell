import os

import pexpect
import pytest

# Path to the shell executable
SHELL_PATH = "./minishell"
TEST_LOG_PATH = "./tests/e2e/log"

# Shell prompt
PROMPT = r"minishell\$ "

if not os.path.exists(TEST_LOG_PATH):
    os.makedirs(TEST_LOG_PATH)


@pytest.fixture(scope="function")
def shell_session(request):
    # Generate log file
    log_file_name = os.path.join(TEST_LOG_PATH, f"{request.function.__name__}.log")

    # Execute shell
    child = pexpect.spawn(SHELL_PATH, encoding="utf-8")
    child.logfile = open(log_file_name, "w")

    # Wait for the shell prompt
    child.expect(PROMPT)

    yield child

    # Close the shell
    child.sendcontrol("D")
    child.close()
    child.logfile.close()
