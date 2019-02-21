import pytest

UNKNOWN_COMMAND = [
    pytest.param("Test", "Unknown command: Test", id="unknown_command"),
]

DATE_WRONG_FORMAT = [
    pytest.param("Add 1-2-3*ff", "Wrong date format: 1-2-3*ff", id="day_invalid"),
    pytest.param("Add 0/12-1 event1", "Wrong date format: 0/12-1", id="1st_separator_invalid"),
    pytest.param("Add 0-12/1 event1", "Wrong date format: 0-12/1", id="2nd_separator_invalid"),
    pytest.param("Add -12-1 event1", "Wrong date format: -12-1", id="empty_year"),
    pytest.param("Add 0--1 event1", "Wrong date format: 0--1", id="empty_month"),
    pytest.param("Add 0-12- event1", "Wrong date format: 0-12-", id="sep_empty_day"),
    pytest.param("Add 0-12 event1", "Wrong date format: 0-12", id="empty_day"),
    pytest.param("Add -- event1", "Wrong date format: --", id="empty_year_month_day"),
    pytest.param("Add - event1", "Wrong date format: -", id="one_sep_only"),
    pytest.param("Add 0 event1", "Wrong date format: 0", id="zero_instead_date"),
    pytest.param("Add 2001-9-0- event1", "Wrong date format: 2001-9-0-", id="full_year_extra_sep"),
    pytest.param("Add --0-12-1 event1", "Wrong date format: --0-12-1", id="extra_sep_in_the_beginning"),
    pytest.param("Add 0---12-1 event1", "Wrong date format: 0---12-1", id="extra_sep_in_the_middle"),
    pytest.param("Add 0-12-1- event1", "Wrong date format: 0-12-1-", id="extra_sep_in_the_end"),
    pytest.param("Add asd-fs-df event1", "Wrong date format: asd-fs-df", id="chars_instead_date"),
    pytest.param("Add asdf-12-1 event1", "Wrong date format: asdf-12-1", id="chars_instead_year"),
    pytest.param("Add 0-kwdfh-1 event1", "Wrong date format: 0-kwdfh-1", id="chars_instead_month"),
    pytest.param("Add 0-12-alskdn event1", "Wrong date format: 0-12-alskdn", id="chars_instead_day")
]

DATE_INVALID = [
    pytest.param("Add 0-13-1 event1", "Month value is invalid: 13", id="month_value_more_than_12"),
    pytest.param("Add 0-0-1 event1", "Month value is invalid: 0", id="month_value_less_than_1"),
    pytest.param("Add 0--13-1 event1", "Month value is invalid: -13", id="negative_month_value"),
    pytest.param("Add 0-12-32 event1", "Day value is invalid: 32", id="day_value_more_than_31"),
    pytest.param("Add 0-12-0 event1", "Day value is invalid: 0", id="day_value_less_than_1"),
    pytest.param("Add 0-12--1 event1", "Day value is invalid: -1", id="negative_day_value"),
    pytest.param("Add 0-13-32 event1", "Month value is invalid: 13", id="month_and_day_values_more_than_valid"),
    pytest.param("Add 0-0-0 event1", "Month value is invalid: 0", id="month_and_day_values_less_than_valid")
]

OPERATIONS = [
    pytest.param("Add 0-12-2 event1", "", id="add"),
    pytest.param("Add 0-1-31 event1\nFind 0-1-31", "event1", id="add_find"),
    pytest.param("Add 0-1-2 event1\nDel 0-1-2", "Deleted 1 events", id="add_del_date"),
    pytest.param("Add 0-1-2 event1\nPrint", "0000-01-02 event1", id="add_print"),
    pytest.param("Add 0-1-2 event1\nDel 0-1-2 event1", "Deleted successfully", id="add_del_event"),
    pytest.param("Del 0-1-2", "Deleted 0 events", id="del_non_exis_date"),
    pytest.param("Del 0-1-2 event1", "Event not found", id="del_non_exis_event"),
    pytest.param("Add 1-2-3 a\nAdd 1-2-3 b\nDel 1-2-3 c", "Event not found", id="add_2_del_non_exis_event")
]