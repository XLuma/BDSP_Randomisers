import sys, os, struct, json

def encode_float(var):
	var = float(var)
	data = int(struct.unpack('<I', struct.pack('<f', var))[0])
	print data
	return 0
def decode_int(var):
	var = int(var)
	data = float(struct.unpack('!f', struct.pack('!I', var & 0xFFFFFFFF))[0])
	print data
	return 0

def main(argc, argv):
	if argc != 3:
		print 'Usage: %s script.py decode/encode integer/float' % argv[0]
		return 1
	if argv[1] == "decode":
		decode_int(argv[2])
	if argv[1] == "encode":
		encode_float(argv[2])
	return 0

if __name__ == '__main__':
    sys.exit(main(len(sys.argv), sys.argv))