import os
import re

import pexpect
import pytest

# Path to the shell executable
SHELL_PATH = "./minishell"
TEST_LOG_PATH = "./tests/e2e/log"

# Shell prompt
PROMPT = r"minishell\$ "


@pytest.fixture(scope="session", autouse=True)
def setup():
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


def clean_output(output):
    # Remove all ANSI escape sequences, including [?2004h and [?2004l
    clean = re.sub(r"\x1b\[[?]?[0-9;]*[a-zA-Z]", "", output)

    # Remove carriage returns and split by newlines
    lines = clean.replace("\r", "").split("\n")

    # Remove empty lines and strip each line
    cleaned_lines = [line.strip() for line in lines if line.strip()]

    # Join the non-empty lines
    return "\n".join(cleaned_lines)


def get_command_output(full_output):
    # Split the output and remove the first line (command)
    output_lines = full_output.split("\n")[1:]

    # Join the remaining lines and clean the output
    return clean_output("\n".join(output_lines))
