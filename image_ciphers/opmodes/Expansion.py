class Expansion(object):
	__expansion_table = [
		31,  0,  1,  2,  3,  4,
		 3,  4,  5,  6,  7,  8,
		 7,  8,  9, 10, 11, 12,
		11, 12, 13, 14, 15, 16,
		15, 16, 17, 18, 19, 20,
		19, 20, 21, 22, 23, 24,
		23, 24, 25, 26, 27, 28,
		27, 28, 29, 30, 31,  0
	]

	__p = [
		1, 2, 3, 4, 5, 8, 9, 10,
		11, 14, 15, 16, 17, 20, 21, 22,
		23, 26, 27, 28, 29, 32, 33, 34,
		35, 38, 39, 40, 41, 44, 45, 46
	]

	def __BitList_to_String(self, data):
		"""Turn the list of bits -> data, into a string"""
		result = []
		pos = 0
		c = 0
		while pos < len(data):
			c += data[pos] << (7 - (pos % 8))
			if (pos % 8) == 7:
				result.append(c)
				c = 0
			pos += 1

		if 2.7 < 3:
			return ''.join([ chr(c) for c in result ])
		else:
			return bytes(result)

	def __permutate(self, table, block):
		"""Permutate this block with the specified table"""
		return list(map(lambda x: block[x], table))

	def __String_to_BitList(self, data):
		"""Turn the string data, into a list of bits (1, 0)'s"""
		if 2.7 < 3:
			# Turn the strings into integers. Python 3 uses a bytes
			# class, which already has this behaviour.
			data = [ord(c) for c in data]
		l = len(data) * 8
		result = [0] * l
		pos = 0
		for ch in data:
			i = 7
			while i >= 0:
				if ch & (1 << i) != 0:
					result[pos] = 1
				else:
					result[pos] = 0
				pos += 1
				i -= 1

		return result


	def __String_to_hex(self, data):
		ords = [ord(c) for c in data]
		hexs = [hex(h) for h in ords]

		return ','.join(hexs)


	def __Hex_to_str(self, data):
		ints = [int(hx,16) for hx in data]
		strs = [str(chr(it)) for it in ints]

		return ''.join(strs)

	def expand(self, fbits):
		"""Return the 6 bytes of expansion en hexadecimal"""
		bitlist = self.__String_to_BitList(fbits)
		expansion = self.__permutate(self.__expansion_table, bitlist)

		expansion_str = self.__BitList_to_String(expansion)
		return self.__String_to_hex(expansion_str)

	def re2(self, hexbytes):
		data = hexbytes.split(',')
		hex_data = self.__Hex_to_str(data)
		expanded_bytes = self.__String_to_BitList(hex_data)
		reduced = self.__permutate(self.__p, expanded_bytes)
		return self.__BitList_to_String(reduced)
