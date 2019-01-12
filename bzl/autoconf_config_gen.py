#!/usr/bin/python2

from __future__ import print_function
import argparse
import re


def split(val):
    result = val.split('=', 1)
    if len(result) == 1:
        return result + ['1']
    return result


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--prefix", default="",
                        help="prepend resulting defines with prefix")
    parser.add_argument("input_file")
    parser.add_argument("output_file")
    parser.add_argument("defines", nargs="*")

    args = parser.parse_args()

    defines = dict(split(x) for x in args.defines)

    undef_re = re.compile(r'^#\s*undef\s+(.*)\s*$')

    with open(args.output_file, 'w') as out, open(args.input_file, 'r') as inp:
        for line in inp:
            match = re.search(undef_re, line)
            if not match:
                out.write(line)
            else:
                name = match.group(1)
                if name in defines:
                    print('#define {}{} {}'.format(args.prefix, name, defines[name]),
                          file=out)
                else:
                    print('/* #undef {}{} */'.format(args.prefix, name),
                          file=out)


if __name__ == '__main__':
    main()
