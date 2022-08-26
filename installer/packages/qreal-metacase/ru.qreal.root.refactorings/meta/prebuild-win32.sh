#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

rsync -a "$BIN_DIR"/plugins/tools/refactoringSupport.dll                        "$PWD"/../data/plugins/tools/
