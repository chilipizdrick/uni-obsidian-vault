import argparse
import os

parser = argparse.ArgumentParser(
    prog='MdMerger',
    description='Merges .md files.',
    epilog='')

parser.add_argument('-i', '--input')
parser.add_argument('-o', '--output')

args = parser.parse_args()

md_files = sorted([file for file in os.scandir(args.input) if file.name.endswith('.md')], key=lambda x: x.name)

output_contents = ''

for md_file in md_files:
    with open(md_file, 'r', encoding='utf-8') as file:
        if file.name != args.output:
            output_contents += file.read() + '\n'

with open(args.output, "w", encoding='utf-8') as out:
    out.write(output_contents)