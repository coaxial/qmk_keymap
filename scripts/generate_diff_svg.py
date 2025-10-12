#!/usr/bin/env python3

import subprocess
import sys
import json
import tempfile
import os

if len(sys.argv) != 4:
    print("Usage: generate_diff_svg.py base.json head.json output.svg")
    sys.exit(1)

base_json = sys.argv[1]
head_json = sys.argv[2]
output_svg = sys.argv[3]

# Load the JSON files
with open(base_json, 'r') as f:
    base_data = json.load(f)

with open(head_json, 'r') as f:
    head_data = json.load(f)

# Assume the layers have the same structure
diff_data = base_data.copy()
diff_data['layers'] = []

for layer_idx, (base_layer, head_layer) in enumerate(zip(base_data['layers'], head_data['layers'])):
    diff_layer = []
    for base_key, head_key in zip(base_layer, head_layer):
        if base_key != head_key:
            diff_key = f"{base_key} -> {head_key}"
        else:
            diff_key = base_key
        diff_layer.append(diff_key)
    diff_data['layers'].append(diff_layer)

# Write the diff data to a temporary file
with tempfile.NamedTemporaryFile(mode='w', suffix='.json', delete=False) as temp_file:
    json.dump(diff_data, temp_file)
    temp_json = temp_file.name

try:
    # Generate the diff SVG using keymap-drawer
    with open(output_svg, 'w') as f:
        subprocess.run(['keymap', 'parse', '-q', temp_json], stdout=subprocess.PIPE, check=True)
        subprocess.run(['keymap', 'draw', '-'], stdin=subprocess.PIPE, stdout=f, check=True, input=subprocess.run(['keymap', 'parse', '-q', temp_json], stdout=subprocess.PIPE, check=True).stdout)
finally:
    os.unlink(temp_json)
