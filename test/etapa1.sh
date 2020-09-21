#!/bin/bash

## etapa1.sh
#
# Copyright: (C) 2020 Henrique Silva
#
# Author: Henrique Silva <hcpsilva@inf.ufrgs.br>
#
# License: GNU General Public License version 3, or any later version
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
## Commentary:
#
# This script runs some test cases for the first stage of INF01147's
# final assignment.
#
## Code:

set -u

TEST_DIR="$(dirname $(readlink -f $0))"
ROOT_DIR="$(dirname $TEST_DIR)"
LOG_FILE="$TEST_DIR/etapa1.log"

echo "$(date)" > $LOG_FILE
echo >> $LOG_FILE
echo >> $LOG_FILE

for test_case in $TEST_DIR/etapa1-cases/*; do
    echo "------------------------------------------------------------" >> $LOG_FILE
    echo "TEST CASE OF FILE '$test_case':" >> $LOG_FILE
    echo >> $LOG_FILE
    $ROOT_DIR/etapa1 < $test_case >> $LOG_FILE
    echo >> $LOG_FILE
done

## etapa1.sh ends here
