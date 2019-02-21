import subprocess
import pytest

SIMPLE_DB_BIN = 'Debug/simple_db'

from tests.simple_db_test_data import UNKNOWN_COMMAND, \
                                DATE_WRONG_FORMAT, \
                                DATE_INVALID, \
                                ADD_AND_FIND_OPERATION_TEST_DATA


def run_simple_db(input):
    simple_db_proc = subprocess.run(SIMPLE_DB_BIN,
                                    capture_output=True,
                                    input=input,
                                    text=True)
    return simple_db_proc.stdout


@pytest.mark.parametrize("input, expected_out", UNKNOWN_COMMAND)
def test_unknown_command(input, expected_out):
    """Если пользователь ввёл неизвестную команду, то программа должна об этом сообщить,
       выведя строку «Unknown command: COMMAND»
    """
    assert run_simple_db(input) == expected_out


@pytest.mark.parametrize("input, expected_out", DATE_WRONG_FORMAT)
def test_date_wrong_format(input, expected_out):
    """Если дата не соответствует формату Год-Месяц-День, где Год, Месяц и День — произвольные целые числа,
       то программа должна напечатать «Wrong date format: DATE», где DATE — это то,
       что пользователь ввёл вместо даты (до пробела).

       Обратите внимание, что части даты разделяются ровно одним дефисом, а сама дата не должна содержать
       лишних символов ни перед годом, ни после дня.

       Части даты не могут быть пустыми, но могут быть нулевыми и даже отрицательными."""
    assert run_simple_db(input) == expected_out


@pytest.mark.parametrize("input, expected_out", DATE_INVALID)
def test_date_invalid(input, expected_out):
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
    assert run_simple_db(input) == expected_out


@pytest.mark.parametrize("input, expected_out", ADD_AND_FIND_OPERATION_TEST_DATA)
def test_add_operation(input, expected_out):
    assert run_simple_db(input).rstrip() == expected_out
