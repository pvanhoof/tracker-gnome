test_c_args = tracker_c_args + [
    '-DTOP_BUILDDIR="@0@"'.format(meson.build_root()),
    '-DTOP_SRCDIR="@0@"'.format(meson.source_root()),
]

date_time_test = executable('tracker-date-time-test',
    'tracker-date-time-test.c',
    dependencies: tracker_miners_common_dep,
    c_args: test_c_args,
)
test('common-date-time', date_time_test)

dbus_test = executable('tracker-dbus-test',
    'tracker-dbus-test.c',
    dependencies: [tracker_miners_common_dep, tracker_testcommon_dep],
    c_args: test_c_args,
)
test('common-dbus', dbus_test)

file_utils_test = executable('tracker-file-utils-test',
    'tracker-file-utils-test.c',
    dependencies: [tracker_miners_common_dep, tracker_testcommon_dep],
    c_args: test_c_args,
)
test('common-file-utils', file_utils_test)

sched_test = executable('tracker-sched-test',
    'tracker-sched-test.c',
    dependencies: [tracker_miners_common_dep, tracker_testcommon_dep],
    c_args: test_c_args,
)
test('common-sched', sched_test)

type_utils_test = executable('tracker-type-utils-test',
    'tracker-type-utils-test.c',
    dependencies: tracker_miners_common_dep,
    c_args: test_c_args,
)
test('common-type-utils', type_utils_test)

utils_test = executable('tracker-utils-test',
    'tracker-utils-test.c',
    dependencies: tracker_miners_common_dep,
    c_args: test_c_args,
)
test('common-utils', utils_test)
