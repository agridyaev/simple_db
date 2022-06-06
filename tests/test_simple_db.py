import subprocess
import pytest


@pytest.fixture
def run_simple_db(binary):
    def inner(command):
        proc = subprocess.run(binary,
                              capture_output=True,
                              input=command,
                              text=True)
        return proc.stdout
    return inner


def test_unknown_command(run_simple_db):
    """Если пользователь ввёл неизвестную команду,
       то программа должна об этом сообщить, выведя строку
       «Unknown command: COMMAND»
    """
    assert run_simple_db("Test") == "Unknown command: Test"


@pytest.mark.parametrize("command, expected_out", [
    pytest.param("Add 1-2-3*ff",           "Wrong date format: 1-2-3*ff"),
    pytest.param("Add 0/12-1 event1",      "Wrong date format: 0/12-1"),
    pytest.param("Add 0-12/1 event1",      "Wrong date format: 0-12/1"),
    pytest.param("Add -12-1 event1",       "Wrong date format: -12-1"),
    pytest.param("Add 0--1 event1",        "Wrong date format: 0--1"),
    pytest.param("Add 0-12- event1",       "Wrong date format: 0-12-"),
    pytest.param("Add 0-12 event1",        "Wrong date format: 0-12"),
    pytest.param("Add -- event1",          "Wrong date format: --"),
    pytest.param("Add - event1",           "Wrong date format: -"),
    pytest.param("Add 0 event1",           "Wrong date format: 0"),
    pytest.param("Add 2001-9-0- event1",   "Wrong date format: 2001-9-0-"),
    pytest.param("Add --0-12-1 event1",    "Wrong date format: --0-12-1"),
    pytest.param("Add 0---12-1 event1",    "Wrong date format: 0---12-1"),
    pytest.param("Add 0-12-1- event1",     "Wrong date format: 0-12-1-"),
    pytest.param("Add asd-fs-df event1",   "Wrong date format: asd-fs-df"),
    pytest.param("Add asdf-12-1 event1",   "Wrong date format: asdf-12-1"),
    pytest.param("Add 0-kwdfh-1 event1",   "Wrong date format: 0-kwdfh-1"),
    pytest.param("Add 0-12-alskdn event1", "Wrong date format: 0-12-alskdn")
])
def test_date_wrong_format(run_simple_db, command, expected_out):
    """Если дата не соответствует формату Год-Месяц-День, где Год, Месяц и День —
       произвольные целые числа, то программа должна напечатать «Wrong date format: DATE»,
       где DATE — это то, что пользователь ввёл вместо даты (до пробела).

       Обратите внимание, что части даты разделяются ровно одним дефисом,
       а сама дата не должна содержать лишних символов ни перед годом, ни после дня.

       Части даты не могут быть пустыми, но могут быть нулевыми и даже отрицательными."""
    assert run_simple_db(command) == expected_out


@pytest.mark.parametrize("command, expected_out", [
    pytest.param("Add 0-13-1 event1",  "Month value is invalid: 13"),
    pytest.param("Add 0-0-1 event1",   "Month value is invalid: 0"),
    pytest.param("Add 0--13-1 event1", "Month value is invalid: -13"),
    pytest.param("Add 0-12-32 event1", "Day value is invalid: 32"),
    pytest.param("Add 0-12-0 event1",  "Day value is invalid: 0"),
    pytest.param("Add 0-12--1 event1", "Day value is invalid: -1"),
    pytest.param("Add 0-13-32 event1", "Month value is invalid: 13"),
    pytest.param("Add 0-0-0 event1",   "Month value is invalid: 0")
])
def test_date_invalid(run_simple_db, command, expected_out):
    """Если формат даты верен, необходимо проверить валидность месяца и дня.

       Если номер месяца не является числом от 1 до 12,
       выведите  «Month value is invalid: MONTH»,
       где MONTH — это неверный номер месяца, например, 13 или -1.

       Если месяц корректен, а день не лежит в диапазоне от 1 до 31,
       выведите «Day value is invalid: DAY»,
       где DAY — это неверный номер дня в месяце, например, 39 или 0.

       Обратите внимание, что:

       Значение года проверять отдельно не нужно.

       Не нужно проверять календарную корректность даты: количество дней
       в каждом месяце считается равным 31, високосные года учитывать не нужно.

       Если неверны как месяц, так и день,
       то нужно вывести одно сообщение об ошибке в месяце.
    """
    assert run_simple_db(command) == expected_out


@pytest.mark.parametrize("command, expected_out", [
    pytest.param("Add 0-12-2 event1",              ""),
    pytest.param("Add 0-1-31 event1\nFind 0-1-31", "event1\n"),
    pytest.param("Add 0-1-2 event1\nDel 0-1-2",    "Deleted 1 events\n"),
    pytest.param("Add 0-1-2 event1\nPrint",        "0000-01-02 event1\n"),
    pytest.param("Del 0-1-2",                      "Deleted 0 events\n"),
    pytest.param("Del 0-1-2 event1",               "Event not found\n"),
    pytest.param("Add 0-1-2 event1\nDel 0-1-2 event1",
                 "Deleted successfully\n"),
    pytest.param("Add 1-2-3 a\nAdd 1-2-3 b\nDel 1-2-3 c",
                 "Event not found\n")
])
def test_positive(run_simple_db, command, expected_out):
    assert run_simple_db(command) == expected_out
