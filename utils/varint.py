#/usr/bin/python3

def vint(*args):
    result = 0
    shift = 0


    for a in args:
        if a & 0x80:
            result |= (a & 0x7f) << shift
            shift += 7
            continue
        result |= a  << shift
        break

    return result
