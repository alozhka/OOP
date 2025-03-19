PROGRAM=$1
OUTPUT="/tmp/output.txt"

$PROGRAM 30 > $OUTPUT
if ! cmp out.txt $OUTPUT ; then
  echo "Find prime numbers failed"
  exit 1
fi

OUT=$($PROGRAM -1)
if [ "$OUT" != "Upper bound must be between 0 and 100000000" ]; then
  echo "Find prime numbers below lower border failed. Got $OUT"
  exit 1
fi

OUT=$($PROGRAM 100000001)
if [ "$OUT" != "Upper bound must be between 0 and 100000000" ]; then
  echo "Find prime numbers above upper border failed. Got $OUT"
  exit 1
fi

echo "All tests finished correctly"