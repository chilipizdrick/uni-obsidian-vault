#!/usr/bin/env bash

set -e

rm -rf ./target/МС_КМБО-03-23_ЕРШОВ_ТР_2
mkdir -p ./target/МС_КМБО-03-23_ЕРШОВ_ТР_2
mkdir -p ./target/МС_КМБО-03-23_ЕРШОВ_ТР_2/МС_КМБО-03-23_ЕРШОВ_ТР_2_ИСХОДНИКИ
typst compile ./src/main.typ ./target/МС_КМБО-03-23_ЕРШОВ_ТР_2/МС_КМБО-03-23_ЕРШОВ_ТР_2.pdf

cp ./src/assets/code/MS_62_4.py ./target/МС_КМБО-03-23_ЕРШОВ_ТР_2/
cp ./src/assets/code/MS_62_5.py ./target/МС_КМБО-03-23_ЕРШОВ_ТР_2/
cp -r ./src/* ./target/МС_КМБО-03-23_ЕРШОВ_ТР_2/МС_КМБО-03-23_ЕРШОВ_ТР_2_ИСХОДНИКИ

