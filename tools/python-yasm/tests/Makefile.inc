# $Id$

EXTRA_DIST += tools/python-yasm/tests/python_test.sh
EXTRA_DIST += tools/python-yasm/tests/__init__.py
EXTRA_DIST += tools/python-yasm/tests/test_intnum.py
EXTRA_DIST += tools/python-yasm/tests/test_symrec.py

if HAVE_PYTHON

TESTS_ENVIRONMENT += PYTHON=${PYTHON}
TESTS += tools/python-yasm/tests/python_test.sh

endif