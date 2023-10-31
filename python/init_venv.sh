#!/bin/bash

VENV_NAME="nmea_parser"

if [ ! -d $VENV_NAME ]; then
    python3 -m venv $VENV_NAME
fi

source $VENV_NAME/bin/activate
pip install matplotlib numpy scipy