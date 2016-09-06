#!/bin/sh

set -eu

ROOT=$(dirname $0)/..

$ROOT/thirdparty/quasardb/bin/qdbd --log-flush-interval=1 --store-history=false --root=$ROOT/db &
sleep 3
PID=$!

function kill_qdbd {
	kill $PID && wait $PID || true
    rm -rf $ROOT/db
}
trap kill_qdbd EXIT

if [[ "$OSTYPE" == "msys" ]]; then
	$ROOT/build/Release/qdb-benchmark $@
else
	$ROOT/build/qdb-benchmark $@
fi
