#!/usr/bin/env python3
import sys

POLY = 0xA001

def crc16(data: bytes, crc: int = 0xFFFF) -> int:
    for b in data:
        crc ^= b
        for _ in range(8):
            if crc & 1:
                crc = (crc >> 1) ^ POLY
            else:
                crc >>= 1
    return crc & 0xFFFF

def main(path: str):
    with open(path, 'rb') as f:
        buf = f.read()
    if len(buf) < 3:
        print('File too short')
        return 1
    data = buf[:-3]
    crc_expected = buf[-3] | (buf[-2] << 8)
    stop_byte = buf[-1]
    crc_calc = crc16(data)
    print('CRC expected:', hex(crc_expected))
    print('CRC calculated:', hex(crc_calc))
    print('Stop byte:', hex(stop_byte))
    if crc_expected == crc_calc:
        print('CRC OK')
    else:
        print('CRC MISMATCH')

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Usage: verify_crc.py <binary_file>')
        sys.exit(1)
    main(sys.argv[1])
