import pytest


def pytest_addoption(parser):
    parser.addoption(
        "--binary",
        action="store",
        default="simple-db",
        help="Simple db binary name"
    )


@pytest.fixture(scope="module")
def binary(request):
    return request.config.getoption("--binary")
