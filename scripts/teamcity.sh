#!/bin/sh

set -eu

echo -n "qdbd args: "
read QDBD_ARGS

echo -n "qdb-benchmark args: "
read BENCH_ARGS

ROOT=$(dirname $0)/..

$ROOT/thirdparty/quasardb/bin/qdbd --root=$ROOT/db $QDBD_ARGS &
sleep 3
PID=$!

function kill_qdbd {
	kill $PID && wait $PID || true
    rm -rf $ROOT/db
}
trap kill_qdbd EXIT

if [[ "$OSTYPE" == "msys" ]]; then
	$ROOT/build/Release/qdb-benchmark $BENCH_ARGS
else
	$ROOT/build/qdb-benchmark $BENCH_ARGS
fi
