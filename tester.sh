#!/bin/bash

EXEC=./cub3D
TEST_DIR=tests

RED="\033[0;31m"
GREEN="\033[0;32m"
NC="\033[0m"

run_test() {
    DESC=$1
    FILE=$2

    echo "Running: $DESC"

    OUTPUT=$($EXEC $FILE 2>&1)

    if echo "$OUTPUT" | grep -i "error" > /dev/null; then
        echo -e "${GREEN}PASS${NC} - Error detected as expected"
    else
        echo -e "${RED}FAIL${NC} - No error detected"
        echo "Output:"
        echo "$OUTPUT"
    fi

    echo "--------------------------------------"
}

echo "========== cub3D Error Tests =========="

# 1. Map not last (wrong order)
run_test "Map not last in file" "$TEST_DIR/wrong_order.cub"

# 2. Missing required items (e.g. missing NO/SO/WE/EA or F/C)
run_test "Missing required elements" "$TEST_DIR/missing_items.cub"

# 3. Invalid texture path
run_test "Invalid texture path" "$TEST_DIR/invalid_texture.cub"

# 4. Invalid item in map
run_test "Invalid item in map" "$TEST_DIR/invalid_item_in_map.cub"

# 5. Map not closed
run_test "Map not closed" "$TEST_DIR/map_not_closed.cub"

echo "============== DONE ==================="