#!/bin/bash

../build/tests/tests > input_data.txt
python3 nmea_parser.py input_data.txt