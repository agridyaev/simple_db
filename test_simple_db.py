import subprocess
import pytest

from simple_db_test_data import UNKNOWN_COMMAND, \
                                DATE_WRONG_FORMAT, \
                                DATE_INVALID, \
                                OPERATIONS


def run_simple_db(simple_db_path, input):
    simple_db_proc = subprocess.run(simple_db_path,
                                    capture_output=True,
                                    input=input,
                                    text=True)
    return simple_db_proc.stdout


@pytest.mark.parametrize("input, expected_out", UNKNOWN_COMMAND)
def test_unknown_command(request, input, expected_out):
    """Если пользователь ввёл неизвестную команду, то программа должна об этом сообщить,
       выведя строку «Unknown command: COMMAND»
    """
    assert run_simple_db(request.config.getoption('--simple-db-path'), input) == expected_out


@pytest.mark.parametrize("input, expected_out", DATE_WRONG_FORMAT)
def test_date_wrong_format(request, input, expected_out):
    """Если дата не соответствует формату Год-Месяц-День, где Год, Месяц и День — произвольные целые числа,
       то программа должна напечатать «Wrong date format: DATE», где DATE — это то,
       что пользователь ввёл вместо даты (до пробела).

       Обратите внимание, что части даты разделяются ровно одним дефисом, а сама дата не должна содержать
       лишних символов ни перед годом, ни после дня.

       Части даты не могут быть пустыми, но могут быть нулевыми и даже отрицательными."""
    assert run_simple_db(request.config.getoption('--simple-db-path'), input) == expected_out


@pytest.mark.parametrize("input, expected_out", DATE_INVALID)
def test_date_invalid(request, input, expected_out):
    """Если формат даты верен, необходимо проверить валидность месяца и дня.

       Если номер месяца не является числом от 1 до 12, выведите «Month value is invalid: MONTH»,
       где MONTH — это неверный номер месяца, например, 13 или -1.

       Если месяц корректен, а день не лежит в диапазоне от 1 до 31, выведите «Day value is invalid: DAY»,
       где DAY — это неверный номер дня в месяце, например, 39 или 0.

       Обратите внимание, что:

       Значение года проверять отдельно не нужно.

       Не нужно проверять календарную корректность даты: количество дней в каждом месяце считается равным 31,
       високосные года учитывать не нужно.

       Если неверны как месяц, так и день, то нужно вывести одно сообщение об ошибке в месяце.
    """
    assert run_simple_db(request.config.getoption('--simple-db-path'), input) == expected_out


@pytest.mark.parametrize("input, expected_out", OPERATIONS)
def test_operations(request, input, expected_out):
    assert run_simple_db(request.config.getoption('--simple-db-path'), input).rstrip() == expected_out
