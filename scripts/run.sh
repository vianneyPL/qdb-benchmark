#!/bin/sh

set -eu

ROOT=$(dirname $0)/..

$ROOT/qdb/bin/qdbd --log-flush-interval=1 &
sleep 3
PID=$!

function kill_qdbd {
	kill $PID && wait $PID || true 
}
trap kill_qdbd EXIT

if [[ "$OSTYPE" == "msys" ]]; then
	$ROOT/build/Release/qdb-benchmark $@
else
	$ROOT/build/qdb-benchmark $@
fi
