def pytest_addoption(parser):
    parser.addoption('--simple-db-path', action='store', dest='stringvalue')
